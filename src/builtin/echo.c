#include "../../include/minishell/builtin.h"

char	ft_is_option(char *arg)
{
	size_t	i;

	if (!arg || !!ft_strncmp(arg, "-n", 2))
		return (false);
	i = 1;
	while (arg[++i])
		if (arg[i] != 'n')
			return (false);
	return (true);
}

int	ft_echo(t_cmds *cmd)
{
	int		i;
	char	nl;

	i = 1;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		while (ft_is_option(cmd->argv[i]))
			i++;
	else if (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
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
