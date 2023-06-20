#include "../../include/minishell/builtin.h"

static int	ft_is_invalid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] != '\0')
	{
		if (ft_strchr(str, '?') || ft_strchr(str, '%') || ft_strchr(str, '/')
			|| ft_strchr(str, '-') || ft_strchr(str, '+')
			|| ft_strchr(str, '='))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_cmds *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!ft_is_invalid(cmd->argv[i]))
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
