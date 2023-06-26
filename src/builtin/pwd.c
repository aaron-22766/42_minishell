#include "../../include/minishell/builtin.h"

int	ft_pwd(t_cmds *cmd)
{
	char	*pwd;

	if ((cmd->argv[0] && !cmd->argv[1])
		|| (cmd->argv[0] && cmd->argv[1][0] != '-'))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			exit(ft_perror_builtin(cmd->argv[0], ERR_ERRNO, cmd->argv[0]));
		printf("%s\n", pwd);
		free(pwd);
		exit(0);
	}
	ft_eprintf("minishell: %s: no options allowed\n", cmd->argv[0]);
	exit(1);
}
