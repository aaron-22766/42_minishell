#include "../../include/minishell/executor.h"

static void	ft_execute_child(int status, t_cmds *cmd)
{
	extern char	**environ;

	if (ft_install_redirections(status, cmd) == RETURN_FAILURE)
		exit(EXIT_FAILURE);
	ft_run_builtin(cmd, NULL);
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
