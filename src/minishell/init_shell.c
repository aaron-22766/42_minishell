#include "../../include/minishell/minishell.h"

static void	ft_allocate_environ(void)
{
	extern char	**environ;
	char		**new;
	int			i;

	new = ft_calloc(ft_environ_size() + 1, sizeof(char *));
	if (new)
	{
		i = -1;
		while (environ[++i])
			new[i] = ft_strdup(environ[i]);
	}
	environ = new;
	if (verbose)
		ft_print_environ();
}

void	ft_init_shell(void)
{
	ft_allocate_environ();
}
