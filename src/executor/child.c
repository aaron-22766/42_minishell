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

static void	ft_redirect(int fd, char std)
{
	if (fd != std && dup2(fd, std) == -1)
		exit(ft_perror(ERR_ERRNO, "failed to dup stdin"));
	if (fd != std)
		close(fd);
	fd = std;
}

static void	ft_execute_child(t_cmds *cmd)
{
	extern char	**environ;

	ft_redirect(cmd->fd_in, STDIN_FILENO);
	ft_redirect(cmd->fd_out, STDOUT_FILENO);
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

int	ft_create_child(t_cmds *cmd)
{
	pid_t	pid;
	int		wait_status;

	if (g_ctrlc == true)
		return (130);
	pid = fork();
	if (pid < 0)
		return (ft_perror(ERR_ERRNO, "fork failed"), RETURN_FAILURE);
	if (pid == 0)
		ft_execute_child(cmd);
	else
	{
		if (waitpid(pid, &wait_status, WUNTRACED) == -1)
			ft_perror(ERR_ERRNO, "waiting for child process failed");
		if (g_ctrlc == true)
			return (printf("\n"), 130);
		return (WEXITSTATUS(wait_status));
	}
	return (RETURN_FAILURE);
}
