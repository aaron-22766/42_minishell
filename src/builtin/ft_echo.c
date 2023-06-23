#include "../../include/minishell/builtin.h"

int	ft_echo(t_cmds *cmd)
{
	int		i;
	char	nl;

	i = 1;
	while (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
		i++;
	nl = (i == 1);
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	exit(0);
}
