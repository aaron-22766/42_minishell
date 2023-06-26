#include "../../include/minishell/minishell.h"

static char	*ft_get_shell(char *ms_path, char *cwd)
{
	char	*new_shell;

	if (!cwd)
		return (NULL);
	if (ms_path[0] == '/')
		return (ft_strdup(ms_path));
	if (!ft_strcmp(ms_path, "./minishell"))
		ms_path = "minishell";
	ft_asprintf(&new_shell, "%s/%s", cwd, ms_path);
	return (free(cwd), new_shell);
}

static void	ft_copy_env(void)
{
	extern char	**environ;
	char		**new;
	int			i;

	new = ft_calloc(ft_environ_size() + 1, sizeof(char *));
	if (!new)
	{
		ft_perror(ERR_MEM, "initializing environment");
		return ;
	}
	i = -1;
	while (environ[++i])
	{
		new[i] = ft_strdup(environ[i]);
		if (!new[i])
		{
			ft_perror(ERR_MEM, "initializing environment");
			ft_free_environ();
			return ;
		}
	}
	environ = new;
}

static void	ft_set_env(char *ms_path)
{
	char	*cwd;
	char	*val;

	ft_putenv("OLDPWD");
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd, 1);
	if (!getenv("SHLVL"))
		ft_putenv("SHLVL=1");
	else
	{
		val = ft_str_add(getenv("SHLVL"), "1");
		if (!val || ft_setenv("SHLVL", val, 1) == -1)
			ft_perror(ERR_MEM, "setting environment variable: SHLVL");
		free(val);
	}
	if (getenv("SHELL"))
	{
		val = ft_get_shell(ms_path, cwd);
		if (!val || ft_setenv("SHELL", val, 1) == -1)
			ft_perror(ERR_MEM, "setting environment variable: SHELL");
		free(val);
	}
}

void	ft_init_shell(char *ms_path)
{
	ft_copy_env();
	ft_set_env(ms_path);
	if (verbose)
	{
		printf("\033[1;33mENVIRONMENT\033[0m\n");
		ft_print_environ();
	}
}
