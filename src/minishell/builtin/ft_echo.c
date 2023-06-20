#include "../../../include/minishell/builtin.h"

void	ft_echo(t_cmds *command)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (command->argv[i] && !ft_strcmp(command->argv[1], "-n"))
	{
		check = 1;
		i++;
	}
	while (command->argv[i])
	{
		printf("%s", command->argv[i]);
		if (command->argv[i] + 1)
			printf(" ");
		i++;
	}
	if (check == 0)
		printf("\n");
	ft_free_commands(command);
	exit(0);
}
