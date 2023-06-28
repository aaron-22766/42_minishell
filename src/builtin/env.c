#include "../../include/minishell/builtin.h"

int	ft_env(t_cmds *cmd)
{
	if (cmd->argv[1])
	{
		ft_eprintf("minishell: %s: no options allowed\n", cmd->argv[0]);
		exit(1);
	}
	ft_print_environ();
	exit(0);
}
