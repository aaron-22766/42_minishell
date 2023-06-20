#include "../../include/minishell/builtin.h"

int	ft_echo(t_cmds *cmd)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (cmd->argv[i] && !ft_strcmp(cmd->argv[1], "-n"))
	{
		check = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i] + 1)
			printf(" ");
		i++;
	}
	if (check == 0)
		printf("\n");
	exit(0);
}
