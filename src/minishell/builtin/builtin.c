#include "../../../include/minishell/minishell.h"

int	ft_builtin(t_cmds *command)
{
	char	*cmd;

	cmd = ft_str_tolower(command->argv[0]);
	if (ft_strcmp("echo", cmd) == 0)
		ft_echo(command);
	else if (ft_strcmp("cd", cmd) == 0)
		ft_cd(command);
	else if (ft_strcmp("pwd", cmd) == 0)
		ft_pwd(command);
	else if (ft_strcmp("export", cmd) == 0)
		ft_export(command);
	else if (ft_strcmp("unset", cmd) == 0)
		ft_unset(command);
	else if (ft_strcmp("env", cmd) == 0)
		ft_env(command);
	else
		ft_execute_cmd(cmd);
	return (free(cmd), 0);
}
