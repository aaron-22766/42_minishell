#include "../../include/minishell/executor.h"

static char	ft_create_pipes(t_cmds *commands)
{
	int	fd[2];

	while (commands && commands->next)
	{
		if (pipe(fd) == -1)
			return (ft_perror(ERR_ERRNO, "pipe creation failed"),
				RETURN_FAILURE);
		commands->fd_out = fd[1];
		commands->next->fd_in = fd[0];
		commands = commands->next;
	}
	return (RETURN_SUCCESS);
}

char	ft_install_redirections(unsigned char status, t_cmds *command)
{
	(void)status;
	(void)command;
	return (RETURN_SUCCESS);
}

char	*ft_find_path(char *name)
{
	(void)name;
	return (ft_strdup("/bin/echo"));
}

void	ft_try_builtin(char **args)
{
	(void)args;
	// if (builtin)
	// 	exit(EXIT_SUCCESS);
}

void	ft_execute_child(unsigned char status, t_cmds *command)
{
	signal(SIGINT, ft_sig_handler);
	if (ft_install_redirections(status, command) == RETURN_FAILURE)
		exit(EXIT_FAILURE);
	command->path = ft_find_path(command->argv[0]);
	if (!command->path)
		exit(EXIT_FAILURE);
	if (g_ctrlc == true)
		exit(130);
	ft_try_builtin(command->argv);
	execve(command->path, command->argv, NULL);
	ft_perror(ERR_ERRNO, "failed to execute command");
	exit(EXIT_FAILURE);
}

unsigned char	ft_create_child(unsigned char status, t_cmds *command)
{
	pid_t	pid;
	int		wait_status;

	if (g_ctrlc == true)
		return (130);
	pid = fork();
	if (pid < 0)
		return (ft_perror(ERR_ERRNO, "fork failed"), RETURN_FAILURE);
	if (pid == 0)
		ft_execute_child(status, command);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(pid, &wait_status, 0) == -1)
			ft_perror(ERR_ERRNO, "waiting for child process failed");
		return (WEXITSTATUS(wait_status));
	}
	return (RETURN_FAILURE);
}

unsigned char	ft_execute(unsigned char status, t_cmds *commands)
{
	system("leaks minishell");
	if (!commands || ft_create_pipes(commands) == RETURN_FAILURE)
		return (ft_free_cmds(commands), RETURN_FAILURE);
	if (verbose)
		print_cmds(commands);
	while (commands)
	{
		status = ft_create_child(status, commands);
		if (status != EXIT_SUCCESS)
			return (ft_free_cmds(commands), status);
		commands = commands->next;
	}
	return (ft_free_cmds(commands), RETURN_SUCCESS);
}
