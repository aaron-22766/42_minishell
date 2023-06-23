#include "../../include/minishell/builtin.h"

void	ft_check_builtin(t_cmds *cmd)
{
	char	*lower;

	if (!cmd->argv)
		return ;
	if (ft_strcmp("export", cmd->argv[0]) == 0)
		cmd->builtin = B_EXPORT;
	else if (ft_strcmp("cd", cmd->argv[0]) == 0)
		cmd->builtin = B_CD;
	else if (ft_strcmp("exit", cmd->argv[0]) == 0)
		cmd->builtin = B_EXIT;
	lower = ft_str_tolower(ft_strdup(cmd->argv[0]));
	if (!lower)
	{
		ft_perror(ERR_MEM, "check builtin failed");
		return ;
	}
	if (ft_strcmp("pwd", lower) == 0)
		cmd->builtin = B_PWD;
	else if (ft_strcmp("unset", lower) == 0)
		cmd->builtin = B_UNSET;
	else if (ft_strcmp("env", lower) == 0)
		cmd->builtin = B_ENV;
	else if (ft_strcmp("echo", lower) == 0)
		cmd->builtin = B_ECHO;
	free(lower);
}

int	ft_run_builtin(t_cmds *cmd)
{
	if (cmd->builtin == B_CD)
		return (ft_cd(cmd));
	if (cmd->builtin == B_EXPORT)
		return (ft_export(cmd));
	if (cmd->builtin == B_PWD)
		return (ft_pwd(cmd));
	if (cmd->builtin == B_UNSET)
		return (ft_unset(cmd));
	if (cmd->builtin == B_ENV)
		return (ft_env(cmd));
	if (cmd->builtin == B_ECHO)
		return (ft_echo(cmd));
	return (EXIT_SUCCESS);
}
