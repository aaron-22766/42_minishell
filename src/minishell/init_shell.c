#include "../../include/minishell/minishell.h"

static char	*ft_get_shell(char *ms_path, char *prev_shell)
{
	char	*cwd;
	char	*new_shell;

	if (ms_path[0] == '/')
	{
		if (ft_asprintf(&new_shell, "SHELL=%s", ms_path) < 0)
			return (ft_perror(ERR_MEM, "creating environment variable: SHELL"),
				ft_strdup(prev_shell));
		return (new_shell);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_perror(ERR_ERRNO, "Current working directory not found"),
			ft_strdup(prev_shell));
	if (!ft_strcmp(ms_path, "./minishell"))
		ms_path = "minishell";
	if (ft_asprintf(&new_shell, "SHELL=%s/%s", cwd, ms_path) < 0)
		return (ft_perror(ERR_MEM, "creating environment variable: SHELL"),
			free(cwd), ft_strdup(prev_shell));
	return (free(cwd), new_shell);
}

static void	ft_allocate_environ(char *ms_path)
{
	extern char	**environ;
	char		**new;
	int			i;

	new = ft_calloc(ft_environ_size() + 1, sizeof(char *));
	if (new)
	{
		i = -1;
		while (environ[++i])
		{
			if (ft_strlen(environ[i]) > 6
				&& !ft_strncmp(environ[i], "SHELL=", 6))
				new[i] = ft_get_shell(ms_path, environ[i]);
			else
				new[i] = ft_strdup(environ[i]);
		}
	}
	environ = new;
}

void	ft_init_shell(char *ms_path)
{
	ft_allocate_environ(ms_path);
	if (verbose)
	{
		printf("\033[1;33mENVIRONMENT\033[0m\n");
		ft_print_environ();
	}
}
