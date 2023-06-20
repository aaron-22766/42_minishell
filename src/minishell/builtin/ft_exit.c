#include "../../../include/minishell/builtin.h"

int	ft_is_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '-' || argv[i] == '+')
			i++;
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_exit(t_cmds *command)
{
	ft_free_commands(command);
	exit(0);
}

void	ft_exit(t_cmds *command)
{
	int	i;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 2)
		printf("exit\nminishell: exit: too many arguments\n");
	if (!command->argv[1])
		ft_free_exit(command);
	if (i == 2)
	{
		if (ft_is_num(command->argv[1]))
		{
			ft_free_commands(command);
			exit(ft_atoi(command->argv[1]));
		}
		else
		{
			printf("exit\nminishell: exit: %s: need numeric argument\n",
				command->argv[1]);
			ft_free_commands(command);
			exit(255);
		}
	}
	ft_free_exit(command);
}
