#include "../../../include/minishell/builtin.h"

int	ft_unset_inv(char *str)
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

void	ft_unset(t_cmds *command)
{
	int	i;

	i = 0;
	while (command->argv[i] && i >= 0)
		i++;
	i--;
	while (i >= 0)
	{
		if (!ft_unset_inv(command->argv[i]))
			ft_unsetenv(command->argv[i]);
		else
		{
			printf("minishell: unset: %s not a valid identifier\n",
				command->argv[i]);
		}
		i--;
	}
}
