#include "../../../include/minishell/minishell.h"

void	ft_cd_error(t_cmds *command, char *error_message)
{
	printf("minishell: cd: %s\n", error_message);
	free_commands(command);
	exit(1);
}

void	ft_set_home_directory(t_cmds *command, char *pwd)
{
	ft_setenv("HOME", pwd, 1);
	ft_free_commands(command);
	exit(0);
}

void	ft_set_pwd_and_oldpwd(t_cmds *command, char *pwd, char *pwdold)
{
	ft_setenv("PWD", pwd, 1);
	ft_setenv("OLDPWD", pwdold, 1);
	free(pwdold);
	free(pwd);
	ft_free_commands(command);
	exit(0);
}

void	ft_handle_cd_error(t_cmds *command, char *pwdold, char *pwd, char c)
{
	if (c == chdir)
	{
		ft_perror_builtin(cd, ERR_ERRNO, "chdir");
		free(pwdold);
		free_commands(command);
		exit(1);
	}
	else if (c == pwdold)
	{
		ft_perror_builtin(cd, ERR_ERRNO, "getcwd");
		ft_free_commands(command);
		exit(1);
	}
	else if (c == pwd)
	{
		ft_perror_builtin(cd, ERR_ERRNO, "getcwd");
		free(pwdold);
		ft_free_commands(command);
		exit(1);
	}
}

void	ft_check_cd(t_cmds *command, char *pwd, char *pwdold)
{
	if (command->argv[1][0] == '-')
		ft_set_pwd_and_oldpwd(command, pwdold, pwd);
	ft_set_pwd_and_oldpwd(command, pwd, pwdold);
}

void	ft_cd(t_cmds *command)
{
	extern char	**environ;
	int			i;
	char		*pwdold;
	char		*pwd;

	i = 0;
	while (command->argv[i])
		i++;
	if (i > 2)
		ft_cd_error(command, "works only with a relative or absolute path");
	pwdold = getcwd(NULL, 0);
	if (pwdold == NULL)
		ft_handle_cd_error(command, pwdold, pwd, pwdold);
	if (!command->argv[1])
		ft_set_home_directory(command, pwd);
	if (chdir(command->argv[1]) == -1)
		ft_handle_cd_error(command, pwdold, pwd, chdir);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		ft_handle_cd_error(command, pwdold, pwd, pwd);
	if (i == 2)
		ft_check_cd(command, pwd, pwdold);
}
