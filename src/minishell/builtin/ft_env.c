#include "../../../include/minishell/builtin.h"

void	ft_env(t_cmds *command)
{
	int			i;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 1)
	{
		printf("minishell: env: use it without options\n");
		ft_free_commands(command);
		exit(1);
	}
	if (i == 1)
	{
		ft_print_environ();
		exit(0);
	}
	exit(1);
}
