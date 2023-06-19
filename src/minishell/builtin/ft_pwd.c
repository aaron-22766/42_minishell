#include "../../../include/minishell/builtin.h"

int	ft_pwd(t_cmds *command)
{
	char	*pwd;

	pwd = NULL;
	if ((command->argv[0] && !command->argv[1])
		|| (command->argv[0] && command->argv[1][0] != '-'))
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			ft_perror_builtin("cd", ERR_ERRNO, "getcwd failed");
			return (1);
		}
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("minishell: pwd: no options available\n");
}
