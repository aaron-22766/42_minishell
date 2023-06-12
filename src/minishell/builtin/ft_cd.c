#include "../../../include/minishell/minishell.h"

// check tilde!
// OLDPWD and PWD
// chdir

void ft_cd_error(t_cmds* command, char* error_message)
{
    printf("minishell: cd: %s\n", error_message);
    free_commands(command);
    exit(1);
}

void ft_set_home_directory(char* pwd)
{
    ft_setenv("HOME", pwd, 1);
}

void ft_set_pwd_and_oldpwd(char* pwd, char* pwdold)
{
    ft_setenv("PWD", pwd, 1);
    ft_setenv("OLDPWD", pwdold, 1);
}

void ft_handle_chdir_error(t_cmds* command, char* pwdold)
{
    perror("chdir");
    free(pwdold);
    free_commands(command);
    exit(1);
}

char	ft_expand_tilde(t_cmds *command, char *pwd)
{
	char	*tmp;
	char	*exp;

	//tmp = ft_set_home_directory(pwd);
	//exp = ft_strjoin(tmp, command[1] + 1)
	//return (exp);
}

void ft_cd(t_cmds* command)
{
    extern char** environ;
    int i;
    char* pwdold;
    char* pwd;

    i = 0;
    while (command->argv[i])
        i++;
    if (i > 2)
        ft_cd_error(command, "works only with a relative or absolute path");
    pwdold = getcwd(NULL, 0);
    if (pwdold == NULL)
	{
        perror("getcwd");
        ft_free_commands(command);
        exit(1);
    }
    if (!command->argv[1])
        ft_set_home_directory(pwd);
    if (chdir(command->argv[1]) == -1)
        ft_handle_chdir_error(command, pwdold);
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
	{
        perror("getcwd");
        free(pwdold);
        ft_free_commands(command);
        exit(1);
    }
    if (i == 2)
	{
        if (command->argv[1][0] == '~')
            ft_expand_tilde(command, pwd);
        ft_set_pwd_and_oldpwd(pwd, pwdold);
        free(pwdold);
        free(pwd);
        ft_free_commands(command);
        exit(0);
    }
    exit(1);
}
