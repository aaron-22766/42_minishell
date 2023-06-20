#include "../../include/minishell/builtin.h"

int	ft_env(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i > 1)
		return (ft_eprintf("minishell: %s: no options allowed", cmd->argv[0]),
			1);
	ft_print_environ();
	return (0);
}
