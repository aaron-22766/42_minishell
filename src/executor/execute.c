#include "../../include/minishell/executor.h"

static char	ft_create_pipes(t_cmds *cmd)
{
	int	fd[2];

	while (cmd && cmd->next)
	{
		if (pipe(fd) == -1)
			return (ft_perror(ERR_ERRNO, "failed to create pipe"),
				RETURN_FAILURE);
		cmd->fd_out = fd[1];
		cmd->next->fd_in = fd[0];
		cmd = cmd->next;
	}
	return (RETURN_SUCCESS);
}

int	ft_execute(int status, t_cmds *commands)
{
	if (ft_create_pipes(commands) == RETURN_FAILURE)
		return (ft_free_cmd(commands), RETURN_FAILURE);
	ft_create_redirections(status, commands);
	ft_check_builtin(commands);
	if (!commands->next && (commands->builtin == B_EXIT))
		ft_exit(commands);//ft_exit(status, commands); + B_CD
	while (commands && g_ctrlc == false)
	{
		ft_check_builtin(commands);
		status = 1;
		if (commands->builtin != B_NO && commands->builtin != B_ECHO)
			status = ft_run_builtin(commands);
		else if (commands->argv)
			status = ft_create_child(commands);
		commands = ft_free_cmd(commands);
	}
	return (ft_free_commands(commands), status);
}
