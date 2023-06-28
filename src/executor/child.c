#include "../../include/minishell/executor.h"

static void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*ft_find_path(char *name)
{
	struct stat	stats;
	char		**paths;
	char		*cmd_path;
	int			i;

	if (!name[0] || !ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		exit(ft_perror(ERR_CMD_NOT_FOUND, name));
	if (ft_strchr(name, '/') || !getenv("PATH"))
	{
		stat(name, &stats);
		if (S_ISDIR(stats.st_mode))
			exit(ft_perror(ERR_IS_DIR, name));
		return (ft_strdup(name));
	}
	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths && paths[++i])
	{
		ft_asprintf(&cmd_path, "%s/%s", paths[i], name);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_paths(paths), cmd_path);
		free(cmd_path);
	}
	ft_free_paths(paths);
	exit(ft_perror(ERR_CMD_NOT_FOUND, name));
}

static char	ft_redirect(int file, int pipe_fd, char std, char condition)
{
	if (file != std)
	{
		if (dup2(file, std) == -1)
			return (RETURN_FAILURE);
		close(file);
		file = std;
		return (RETURN_SUCCESS);
	}
	if (condition && dup2(pipe_fd, std) == -1)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

void	ft_child(t_cmds *cmd, int fd[2], int pipe_in)
{
	extern char	**environ;
	char		red;

	red = (ft_redirect(cmd->fd_in, pipe_in, STDIN_FILENO, (pipe_in != -1))
			|| ft_redirect(cmd->fd_out, fd[1], STDOUT_FILENO, !!cmd->next));
	ft_close_fds(pipe_in, fd, !!cmd->next);
	if (red == RETURN_FAILURE)
	{
		ft_perror(ERR_ERRNO, "dup");
		exit(1);
	}
	ft_run_builtin(cmd);
	cmd->path = ft_find_path(cmd->argv[0]);
	if (g_ctrlc == true)
		exit(130);
	execve(cmd->path, cmd->argv, environ);
	ft_perror(ERR_ERRNO, cmd->argv[0]);
	if (errno == 2)
		exit(127);
	if (errno == 13)
		exit(126);
	exit(errno);
}
