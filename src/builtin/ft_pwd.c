#include "../../include/minishell/builtin.h"

int	ft_pwd(t_cmds *cmd)
{
	char	*pwd;

	if ((cmd->argv[0] && !cmd->argv[1])
		|| (cmd->argv[0] && cmd->argv[1][0] != '-'))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (ft_perror_builtin("cd", ERR_ERRNO, cmd->argv[0]));
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		return (ft_eprintf("minishell: %s: no options allowed\n", cmd->argv[0]),
			1);
	return (0);
}
