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

int	ft_execute(int status, t_cmds *commands)
{
	if (ft_create_pipes(commands) == RETURN_FAILURE)
		return (ft_free_cmd(commands), RETURN_FAILURE);
	ft_create_redirections(status, commands);
	if (ft_single_builtin(&status, commands) == true)
		return (ft_free_commands(commands), status);
	while (commands && g_ctrlc == false)
	{
		ft_check_builtin(commands);
		status = 1;
		if (commands->argv)
			status = ft_create_child(commands);
		commands = ft_free_cmd(commands);
	}
	return (ft_free_commands(commands), status);
}
