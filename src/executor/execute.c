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

unsigned char	ft_execute(unsigned char status, t_cmds *commands)
{
	t_cmds	*cmd;

	if (!commands || ft_create_pipes(commands) == RETURN_FAILURE)
		return (ft_free_cmds(commands), RETURN_FAILURE);
	if (verbose)
	{
		print_cmds(commands);
		printf("\e[1;33mOUTPUT\e[0m\n");
	}
	cmd = commands;
	while (cmd)
	{
		status = ft_create_child(status, cmd, commands);
		cmd = cmd->next;
	}
	return (ft_free_cmds(commands), RETURN_SUCCESS);
}
