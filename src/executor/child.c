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
	char	**paths;
	char	*cmd_path;
	int		i;

	if (ft_strchr(name, '/'))
	{
		if (access(name, F_OK) == 0)
			return (ft_strdup(name));
		exit(ft_perror(ERR_NO_FILE, name));
	}
	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths && paths[++i])
	{
		ft_asprintf(&cmd_path, "%s/%s", paths[i], name);
		if (cmd_path && access(cmd_path, F_OK) == 0)
			return (ft_free_paths(paths), cmd_path);
		free(cmd_path);
	}
	ft_free_paths(paths);
	exit(ft_perror(ERR_CMD_NOT_FOUND, name));
}

static void	ft_execute_child(int status, t_cmds *cmd)
{
	extern char	**environ;

	if (ft_install_redirections(status, cmd) == RETURN_FAILURE)
		exit(EXIT_FAILURE);
	if (!cmd->argv)
		exit(EXIT_SUCCESS);
	ft_run_builtin(cmd);
	cmd->path = ft_find_path(cmd->argv[0]);
	if (g_ctrlc == true)
		exit(130);
	execve(cmd->path, cmd->argv, environ);
	ft_perror(ERR_ERRNO, "failed to execute command");
	exit(EXIT_FAILURE);
}

int	ft_create_child(int status, t_cmds *cmd)
{
	pid_t	pid;
	int		wait_status;

	if (g_ctrlc == true)
		return (130);
	pid = fork();
	if (pid < 0)
		return (ft_perror(ERR_ERRNO, "fork failed"), RETURN_FAILURE);
	if (pid == 0)
		ft_execute_child(status, cmd);
	else
	{
		if (waitpid(pid, &wait_status, 0) == -1)
			ft_perror(ERR_ERRNO, "waiting for child process failed");
		if (g_ctrlc == true)
			return (printf("\n"), 130);
		return (WEXITSTATUS(wait_status));
	}
	return (RETURN_FAILURE);
}
