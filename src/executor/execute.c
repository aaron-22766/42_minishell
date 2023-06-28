#include "../../include/minishell/executor.h"

static char	ft_single_builtin(int *status, t_cmds *commands)
{
	ft_check_builtin(commands);
	if (!commands->next && commands->builtin == B_EXPORT && commands->argv[1])
		*status = ft_export(commands);
	else if (!commands->next && commands->builtin == B_EXIT)
		*status = ft_exit(*status, commands);
	else if (!commands->next && commands->builtin == B_CD)
		*status = ft_cd(commands);
	else if (!commands->next && commands->builtin == B_UNSET)
		*status = ft_unset(commands);
	else
		return (false);
	return (true);
}

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

static char	ft_redirect(int fd, char std)
{
	char	ret;

	ret = (fd != std);
	if (ret && dup2(fd, std) == -1)
		exit(ft_perror(ERR_ERRNO, "dup"));
	if (ret)
		close(fd);
	fd = std;
	return (ret);
}
// close fds on exit & return
static int	ft_pipeline(t_cmds *cmd, int pipe_in)
{
	extern char	**environ;
	pid_t	pid;
	int		fd[2];
	int		wait_status;
	int		status;

	if (g_ctrlc == true)
		return (130);
	ft_check_builtin(cmd);
	if (!cmd->argv)
	{
		if (cmd->next)
			return (ft_pipeline(cmd->next, -1));
		return (RETURN_FAILURE);
	}
	if ((cmd->builtin & B_PARENT)
		&& !(cmd->builtin == B_EXPORT && !cmd->argv[1]))
	{
		if (cmd->next)
			return (ft_pipeline(cmd->next, -1));
		return (RETURN_SUCCESS);
	}
	if (g_ctrlc == true)
		return (130);
	if (cmd->next && pipe(fd) == -1)
		return (ft_perror(ERR_ERRNO, "pipe"), RETURN_FAILURE);
	pid = fork();
	if (pid < 0)
		return (ft_perror(ERR_ERRNO, "fork"), RETURN_FAILURE);
	if (pid == 0)
	{
		if (ft_redirect(cmd->fd_in, STDIN_FILENO) == false)
			if (pipe_in != -1 && dup2(pipe_in, STDIN_FILENO) == -1)
				exit(1);
		if (ft_redirect(cmd->fd_out, STDOUT_FILENO) == false)
			if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
		if (pipe_in != -1)
			close(pipe_in);
		if (cmd->next)
		{
			close(fd[0]);
			close(fd[1]);
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
	if (pipe_in != -1)
		close(pipe_in);
	if (cmd->next)
	{
		close(fd[1]);
		status = ft_pipeline(cmd->next, fd[0]);
	}
	if (waitpid(pid, &wait_status, WUNTRACED) == -1)
		return (ft_perror(ERR_ERRNO, "waitpid"));
	if (!cmd->next)
		status = WEXITSTATUS(wait_status);
	return (status);
}

int	ft_execute(int status, t_cmds *commands)
{
	if (ft_single_builtin(&status, commands) == true)
		return (ft_free_commands(commands), status);
	ft_create_redirections(status, commands);
	// printf("in: %d out: %d\n", commands->fd_in, commands->fd_out);
	status = ft_pipeline(commands, -1);
	waitpid(-1, NULL, WUNTRACED);
	if (g_ctrlc == true)
		printf("\n");
	return (ft_free_commands(commands), status);
}
