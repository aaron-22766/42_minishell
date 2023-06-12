#include "../../../include/minishell/minishell.h"

int	ft_unset_inv(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(str, '?') || ft_strchr(str, '$') || ft_strchr(str, '%')
			|| ft_strchr(str, '-') || ft_strchr(str, '=') || ft_strchr(str, '/'))
			return (1);
		if (ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_cmds *command)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 1)
	{
		printf("minishell: unset: use it without options\n");
		ft_free_commands(command);
		exit(1);
	}
	if (i == 1)
	{
		if (!ft_unset_inv(command->argv[i]))
			ft_unsetenv(command->argv[i]);
		else
			printf("minishell: unset: not a valid identifier\n");
		i++;
	}
	ft_free_commands(command);
}
