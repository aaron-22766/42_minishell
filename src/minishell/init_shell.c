#include "../../include/minishell/minishell.h"

static char	*ft_get_shell(char *prev_shell)
{
	char	*cwd;
	char	*new_shell;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror(ERR_ERRNO, "Current working directory not found");
		return (ft_strdup(prev_shell));
	}
	if (ft_asprintf(&new_shell, "SHELL=%s/minishell", cwd) < 0)
	{
		ft_perror(ERR_MEM, "creating environment variable: SHELL");
		return (free(cwd), ft_strdup(prev_shell));
	}
	return (free(cwd), new_shell);
}

static void	ft_allocate_environ(void)
{
	extern char	**environ;
	char		**new;
	int			i;

	new = ft_calloc(ft_environ_size() + 1, sizeof(char *));
	if (!new)
	{
		environ = NULL;
		return ;
	}
	i = -1;
	while (environ[++i])
	{
		if (ft_strlen(environ[i]) > 6 && !ft_strncmp(environ[i], "SHELL=", 6))
			new[i] = ft_get_shell(environ[i]);
		else
			new[i] = ft_strdup(environ[i]);
	}
	environ = new;
}

void	ft_init_shell(void)
{
	ft_allocate_environ();
	if (verbose)
	{
		printf("\033[1;33mENVIRONMENT\033[0m\n");
		ft_print_environ();
	}
}
