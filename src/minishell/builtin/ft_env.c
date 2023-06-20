#include "../../../include/minishell/builtin.h"

void	ft_env(t_cmds *command)
{
	int			i;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 1)
	{
		ft_perror_builtin("env", ERR_ERRNO, "use command without options");
		ft_free_commands(command);
	}
	if (i == 1)
		ft_print_environ();
}
