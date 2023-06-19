#include "../../../include/minishell/builtin.h"

int	ft_check_builtin_parent(t_cmds *command)
{
	char	*cmd;

	if (ft_strcmp("export", command->argv[0]) == 0)
		ft_export(command);
	else if (ft_strcmp("cd", command->argv[0]) == 0)
		ft_cd(command);
	cmd = ft_str_tolower(command->argv[0]);
	if (ft_strcmp("pwd", cmd) == 0)
		ft_pwd(command);
	else if (ft_strcmp("exit", cmd) == 0)
		ft_exit(command);
	else if (ft_strcmp("unset", cmd) == 0)
		ft_unset(command);
	else if (ft_strcmp("env", cmd) == 0)
		ft_env(command);
	return (0);
}

int	ft_check_builtin_child(t_cmds *command)
{
	char	*cmd;

	cmd = ft_str_tolower(command->argv[0]);
	if (ft_strcmp("echo", cmd) == 0)
		ft_echo(command);
	return (0);
}
