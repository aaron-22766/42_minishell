#include "minishell.h"

static bool	ft_is_default_env_var(char *var)
{
	return (ft_is_env_var(var, "PATH", 4) || ft_is_env_var(var, "USER", 4)
		|| ft_is_env_var(var, "PWD", 3) || ft_is_env_var(var, "HOME", 4));
}

void	ft_init_shell(void)
{
	extern char	**environ;
	char		**new;
	int			i;
	int			n;

	new = ft_calloc(5, sizeof(char *));
	if (new)
	{
		n = 0;
		i = -1;
		while (environ[++i])
			if (ft_is_default_env_var(environ[i]))
				new[n++] = ft_strdup(environ[i]);
	}
	environ = new;
	if (verbose)
		ft_print_environ();
	printf("--------\n");
	ft_unsetenv("PWD");
	if (verbose)
		ft_print_environ();
}
