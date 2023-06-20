#include "../../include/minishell/builtin.h"

// int	ft_hyphen(char *pwd)
// {
// 	char	*pwd_new;

// 	printf("%s\n", getcwd(NULL, 0));
// 	pwd_new = getenv("OLDPWD");
// 	if (!pwd_new)
// 		return (free(pwd), ft_perror_builtin("cd", ERR_CUSTOM, "OLDPWD not set"));
// 	if (chdir(pwd_new) != 0)
// 		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, pwd_new));
// 	ft_setenv("OLDPWD", pwd, 1);
// 	ft_setenv("PWD", pwd_new, 1);
// 	return (0);
// }

// int	ft_dot(char *pwd)
// {
// 	if (chdir("..") != 0)
// 		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, ));
// 	ft_setenv("OLDPWD", pwd, 1);
// 	ft_setenv("PWD", getcwd(NULL, 0), 1);
// 	return (0);
// }

static int	ft_cd_custom(char *pwd, char *env)
{
	char	*new_pwd;

	new_pwd = getenv(env);
	if (!new_pwd)
		return (free(pwd), ft_perror_builtin("cd", ERR_NOT_SET, env));
	if (chdir(new_pwd) == -1)
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, new_pwd));
	ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", new_pwd, 1);
	return (0);
}

static int	ft_cd_path(t_cmds *cmd, char *pwd)
{
	char	*pwd_new;

	if (chdir(cmd->argv[1]) != 0)
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, cmd->argv[1]));
	pwd_new = getcwd(NULL, 0);
	if (!pwd_new)
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, cmd->argv[1]));
	ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", pwd_new, 1);
	return (0);
}

// int	ft_cd_home(char *pwd)
// {
// 	char	*home;

// 	home = getenv("HOME");
// 	if (!home)
// 		return (free(pwd), ft_perror_builtin("cd", ERR_CUSTOM, "HOME not set"));
// 	if (chdir(home) == -1)
// 		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, home));
// 	ft_setenv("OLDPWD", pwd, 1);
// 	ft_setenv("PWD", home, 1);
// 	return (0);
// }

int	ft_cd(t_cmds *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_perror_builtin("cd", ERR_ERRNO, "getcwd failed"));
	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "--") == 0)
		return (ft_cd_custom(pwd, "HOME"));
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		printf("%s\n", getcwd(NULL, 0));
		ft_cd_custom(pwd, "OLDPWD");
	}
	else
		ft_cd_path(cmd, pwd);
	// else if (ft_strcmp(cmd->argv[1], "..") == 0
	// 	|| ft_strcmp(cmd->argv[1], "../") == 0)
	// 	ft_dot(pwd);
	return (0);
}
