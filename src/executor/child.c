#include "../../include/minishell/executor.h"

static void	ft_try_builtin(char **args, t_cmds *commands)
{
	(void)args;
	(void)commands;
	// if (builtin)
	// 	exit(EXIT_SUCCESS);
}

static char	*ft_find_path(char *name)
{
	(void)name;
	return (ft_strdup("/bin/echo"));
}

static void	ft_execute_child(unsigned char status, t_cmds *cmd,
			t_cmds *commands)
{
	signal(SIGINT, ft_sig_handler);
	if (ft_install_redirections(status, cmd) == RETURN_FAILURE)
	{
		ft_free_cmds(commands);
		exit(EXIT_FAILURE);
	}
	ft_try_builtin(cmd->argv, commands);
	cmd->path = ft_find_path(cmd->argv[0]);
	if (!cmd->path)
	{
		ft_free_cmds(commands);
		exit(EXIT_FAILURE);
	}
	if (g_ctrlc == true)
	{
		ft_free_cmds(commands);
		exit(130);
	}
	execve(cmd->path, cmd->argv, NULL);
	ft_perror(ERR_ERRNO, "failed to execute command");
	ft_free_cmds(commands);
	exit(EXIT_FAILURE);
}

unsigned char	ft_create_child(unsigned char status, t_cmds *cmd,
				t_cmds *commands)
{
	pid_t	pid;
	int		wait_status;

	if (g_ctrlc == true)
		return (130);
	pid = fork();
	if (pid < 0)
		return (ft_perror(ERR_ERRNO, "fork failed"), RETURN_FAILURE);
	if (pid == 0)
		ft_execute_child(status, cmd, commands);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &wait_status, 0) == -1)
			ft_perror(ERR_ERRNO, "waiting for child process failed");
		return (WEXITSTATUS(wait_status));
	}
	return (RETURN_FAILURE);
}
