#include "../../../include/minishell/builtin.h"

int	ft_dot_hyphen(char *pwd, char *c)
{
	char	*pwd_new;

	if (ft_strcmp(c, "dot") == 0)
	{
		if (chdir("..") != 0)
		{
			ft_perror_builtin("cd", ERR_ERRNO, "chdir failed");
			return (free(pwd), 1);
		}
		ft_setenv("OLDPWD", pwd, 1);
		ft_setenv("PWD", getcwd(NULL, 0), 1);
	}
	else if (ft_strcmp(c, "hyphen") == 0)
	{
		printf("%s\n", getcwd(NULL, 0));
		pwd_new = getenv("OLDPWD");
		if (chdir(pwd_new) != 0)
		{
			ft_perror_builtin("cd", ERR_ERRNO, "chdir failed");
			return (free(pwd), 1);
		}
		ft_setenv("OLDPWD", pwd, 1);
		ft_setenv("PWD", pwd_new, 1);
	}
	return (0);
}

int	ft_cd_path(t_cmds *command, char *pwd)
{
	char	*pwd_new;

	if (chdir(command->argv[1]) != 0)
	{
		ft_perror_builtin("cd", ERR_ERRNO, "chdir failed");
		free(pwd);
		return (1);
	}
	pwd_new = getcwd(NULL, 0);
	ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", pwd_new, 1);
	return (0);
}

void	ft_check_cd(t_cmds *command, char *pwd)
{
	if (ft_strcmp(command->argv[1], "-") == 0)
	{
		ft_dot_hyphen(pwd, "hyphen");
	}
	else if (ft_strcmp(command->argv[1], "..") == 0
		|| ft_strcmp(command->argv[1], "../") == 0)
	{
		ft_dot_hyphen(pwd, "dot");
	}
	else
		ft_cd_path(command, pwd);
}

int	ft_cd_home(char *pwd)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_perror_builtin("cd", ERR_ERRNO, "getenv failed");
		free(pwd);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_perror_builtin("cd", ERR_ERRNO, "chdir failed");
		free(pwd);
		return (1);
	}
	ft_setenv("OLDPWD", pwd, 1);
	ft_setenv("PWD", home, 1);
	return (0);
}

int	ft_cd(t_cmds *command)
{
	int		i;
	char	*pwd;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 2)
		ft_perror_builtin("cd", ERR_ERRNO, "only a relative or absolute path");
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror_builtin("cd", ERR_ERRNO, "getcwd failed");
		return (1);
	}
	if (!command->argv[1] || ft_strcmp(command->argv[1], "--") == 0)
		return (ft_cd_home(pwd));
	else if (i == 2)
		ft_check_cd(command, pwd);
	return (0);
}
