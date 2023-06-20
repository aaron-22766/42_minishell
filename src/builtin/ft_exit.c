#include "../../include/minishell/builtin.h"

static int	ft_is_num(char *argv)
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

static void	ft_free_exit(t_cmds *commands, int code)
{
	ft_free_commands(commands);
	exit(code);
}

int	ft_exit(t_cmds *cmd, t_cmds *commands)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i > 2)
		return (ft_eprintf("exit\nminishell: exit: too many arguments\n"));
	if (!cmd->argv[1])
		ft_free_exit(commands, 0);
	printf("exit\n");
	if (ft_is_num(cmd->argv[1]))
		ft_free_exit(commands, ft_atoi(cmd->argv[1]));
	else
	{
		ft_eprintf("minishell: exit: %s: need numeric argument\n", cmd->argv[1]);
		ft_free_exit(commands, 255);
	}
	ft_free_exit(commands, 0);
	return (-1);
}
