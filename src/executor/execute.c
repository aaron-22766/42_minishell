#include "../../include/minishell/executor.h"

static char	ft_create_pipes(t_cmds *cmd)
{
	int	fd[2];

	while (cmd && cmd->next)
	{
		if (pipe(fd) == -1)
			return (ft_perror(ERR_ERRNO, "pipe creation failed"),
				RETURN_FAILURE);
		cmd->fd_out = fd[1];
		cmd->next->fd_in = fd[0];
		cmd = cmd->next;
	}
	return (RETURN_SUCCESS);
}

int	ft_execute(int status, t_cmds *commands)
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
	ft_check_builtin(cmd);
	if (!cmd->next && cmd->builtin == B_EXIT)
		ft_exit(cmd);
	while (cmd && g_ctrlc == false)
	{
		ft_check_builtin(cmd);
		if (cmd->builtin != B_NO && cmd->builtin != B_ECHO)
			status = ft_run_builtin(cmd);
		else
			status = ft_create_child(status, cmd);
		if (cmd->next)
			close(cmd->fd_out);
		if (cmd != commands)
			close(cmd->fd_in);
		cmd = cmd->next;
	}
	return (ft_free_cmds(commands), status);
}
