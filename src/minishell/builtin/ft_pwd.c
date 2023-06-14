#include "../../../include/minishell/builtin.h"

void	ft_pwd(t_cmds *command)
{
	char	*pwd;

	pwd = NULL;
	if (command->argv[0])
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
	}
	else
		printf("minishell: pwd: no options available\n");
	ft_free_commands(command);
	free(pwd);
	exit(0);
}
