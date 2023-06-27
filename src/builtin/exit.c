#include "../../include/minishell/builtin.h"

static void	ft_free_exit(t_cmds *cmd, int code)
{
	ft_free_commands(cmd);
	ft_free_environ();
	exit(code);
}

static void	ft_numeric_arg_required(t_cmds *cmd)
{
	ft_eprintf("minishell: exit: %s: numeric argument required\n",
		cmd->argv[1]);
	ft_free_exit(cmd, 255);
}

static char	ft_is_num(char *argv)
{
	size_t	i;

	i = 0;
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (false);
		i++;
	}
	return (!!i);
}

int	ft_exit(int status, t_cmds *cmd)
{
	long long	ret;

	if (!cmd->argv[1])
		ft_free_exit(cmd, status);
	// ft_eprintf("exit\n");//!!!!!!!!!!!!!!!!uncomment
	if (ft_is_num(cmd->argv[1]) == false)
		ft_numeric_arg_required(cmd);
	if (cmd->argv[2])
		return (ft_eprintf("minishell: exit: too many arguments\n"), 1);
	ret = ft_atoll(cmd->argv[1]);
	if ((ret == 0 && !!ft_strcmp(cmd->argv[1], "0"))
		|| (ret == -1 && !!ft_strcmp(cmd->argv[1], "-1")))
		ft_numeric_arg_required(cmd);
	ft_free_exit(cmd, ret);
	return (1);
}
