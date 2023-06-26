#include "../../include/minishell/builtin.h"

void	ft_check_builtin(t_cmds *cmd)
{
	char	*lower;

	if (!cmd->argv)
		return ;
	if (!ft_strcmp("cd", cmd->argv[0]))
		cmd->builtin = B_CD;
	else if (!ft_strcmp("exit", cmd->argv[0]))
		cmd->builtin = B_EXIT;
	else if (!ft_strcmp("unset", cmd->argv[0]))
		cmd->builtin = B_UNSET;
	else if (!ft_strcmp("export", cmd->argv[0]))
		cmd->builtin = B_EXPORT;
	lower = ft_str_tolower(ft_strdup(cmd->argv[0]));
	if (!lower)
		return ;
	if (!ft_strcmp("pwd", lower))
		cmd->builtin = B_PWD;
	else if (!ft_strcmp("env", lower))
		cmd->builtin = B_ENV;
	else if (!ft_strcmp("echo", lower))
		cmd->builtin = B_ECHO;
	free(lower);
}

int	ft_run_builtin(t_cmds *cmd)
{
	if (cmd->builtin == B_PWD)
		return (ft_pwd(cmd));
	if (cmd->builtin == B_UNSET)
		return (ft_unset(cmd));
	if (cmd->builtin == B_ECHO)
		return (ft_echo(cmd));
	if (cmd->builtin == B_ENV)
		return (ft_env(cmd));
	if (cmd->builtin == B_EXPORT)
	{
		if (cmd->argv[1])
			return (ft_export(cmd));
		exit(ft_print_export());
	}
	return (EXIT_SUCCESS);
}
