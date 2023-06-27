#include "../../include/minishell/builtin.h"

void	ft_check_builtin(t_cmds *cmd)
{
	char	*lower;

	if (!cmd->argv)
		return ;
	if (!ft_strcmp(cmd->argv[0], "cd"))
		cmd->builtin = B_CD;
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		cmd->builtin = B_EXIT;
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		cmd->builtin = B_UNSET;
	else if (!ft_strcmp(cmd->argv[0], "export"))
		cmd->builtin = B_EXPORT;
	lower = ft_str_tolower(ft_strdup(cmd->argv[0]));
	if (!lower)
		return ;
	if (!ft_strcmp(lower, "pwd"))
		cmd->builtin = B_PWD;
	else if (!ft_strcmp(lower, "env"))
		cmd->builtin = B_ENV;
	else if (!ft_strcmp(lower, "echo"))
		cmd->builtin = B_ECHO;
	free(lower);
}

int	ft_run_builtin(t_cmds *cmd)
{
	if (cmd->builtin == B_PWD)
		return (ft_pwd(cmd));
	if (cmd->builtin == B_ECHO)
		return (ft_echo(cmd));
	if (cmd->builtin == B_ENV)
		return (ft_env(cmd));
	if (cmd->builtin == B_EXPORT && !cmd->argv[1])
		ft_print_export();
	else if (cmd->builtin & B_PARENT)
		exit(0);
	return (EXIT_SUCCESS);
}
