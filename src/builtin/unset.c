#include "../../include/minishell/builtin.h"

int	ft_unset(t_cmds *cmd)
{
	int	status;
	int	i;

	if (cmd->argv[1] && cmd->argv[1][0] == '-')
		return (ft_eprintf("minishell: export: -%c: invalid option\n",
				cmd->argv[1][1]), 2);
	status = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (ft_valid_identifier(cmd->argv[i], '\0') == true)
			ft_unsetenv(cmd->argv[i]);
		else
		{
			ft_eprintf("minishell: unset: `%s' not a valid identifier\n",
				cmd->argv[i]);
			status = 1;
		}
	}
	return (status);
}
