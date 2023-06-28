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

int	ft_execute(int status, t_cmds *commands)
{
	if (ft_single_builtin(&status, commands) == true)
		return (ft_free_commands(commands), status);
	ft_create_redirections(status, commands);
	status = ft_pipeline(commands, -1);
	waitpid(-1, NULL, WUNTRACED);
	if (g_ctrlc == true)
		printf("\n");
	return (ft_free_commands(commands), status);
}
