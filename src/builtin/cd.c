#include "../../include/minishell/builtin.h"

static int	ft_cd_env(char *pwd, char *env)
{
	char	*new_pwd;

	new_pwd = getenv(env);
	if (!new_pwd)
		return (free(pwd), ft_perror_builtin("cd", ERR_NOT_SET, env));
	if (chdir(new_pwd) == -1)
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, env));
	ft_setenv("OLDPWD", pwd, 1);
	free(pwd);
	ft_setenv("PWD", new_pwd, 1);
	return (0);
}

static int	ft_cd_path(t_cmds *cmd, char *pwd)
{
	char	*new_pwd;

	if (chdir(cmd->argv[1]))
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, cmd->argv[1]), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(pwd), ft_perror_builtin("cd", ERR_ERRNO, cmd->argv[1]), 1);
	ft_setenv("OLDPWD", pwd, 1);
	free(pwd);
	ft_setenv("PWD", new_pwd, 1);
	free(new_pwd);
	return (0);
}

int	ft_cd(t_cmds *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_perror_builtin("cd", ERR_ERRNO, "getcwd failed"));
	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "--") == 0)
		return (ft_cd_env(pwd, "HOME"));
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		if (getenv("OLDPWD"))
			printf("%s\n", getenv("OLDPWD"));
		return (ft_cd_env(pwd, "OLDPWD"));
	}
	return (ft_cd_path(cmd, pwd));
}
