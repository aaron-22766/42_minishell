#include "../../include/minishell/builtin.h"

int	ft_unset(t_cmds *cmd)
{
	int	status;
	int	i;

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
