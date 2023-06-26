#include "../../include/minishell/builtin.h"

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
	free(pwd);
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
		if (getenv("OLDPWD"))
			printf("%s\n", getenv("OLDPWD"));
		return (ft_cd_custom(pwd, "OLDPWD"));
	}
	return (ft_cd_path(cmd, pwd));
}
