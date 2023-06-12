#include "../../../include/minishell/minishell.h"

int	ft_builtin(t_cmds *command)
{
	char	*cmd;

	cmd = ft_str_tolower(command->argv[0]);
	if (ft_strcmp("echo", cmd) == 0)
		ft_echo();
	else if (ft_strcmp("cd", cmd) == 0)
		ft_cd();
	else if (ft_strcmp("pwd", cmd) == 0)
		ft_pwd();
	else if (ft_strcmp("export", cmd) == 0)
		ft_export();
	else if (ft_strcmp("unset", cmd) == 0)
		ft_unset();
	else if (ft_strcmp("env", cmd) == 0)
		ft_env();
	else
		ft_execute_cmd(cmd);
	return(free(cmd), 0);
}
