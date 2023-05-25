#include "minishell.h"

size_t	ft_environ_size(void)
{
	extern char	**environ;
	size_t		size;

	size = 0;
	while (environ[size])
		size++;
	return (size);
}

bool	ft_is_env_var(const char *var1, const char *var2, size_t name_len)
{
	if (!var1 || name_len < 1 || ft_strlen(var1) < name_len + 2)
		return (false);
	return (!ft_strncmp(var1, var2, name_len) && var1[name_len] == '=');
}

int	ft_existing_env_var(const char *var, size_t name_len)
{
	extern char	**environ;
	int			existing;
	int			i;

	if (!var || name_len < 3)
		return (-1);
	existing = -1;
	i = -1;
	while (environ[++i])
		if (ft_is_env_var(environ[i], var, name_len))
			existing = i;
	return (existing);
}

void	ft_print_environ(void)
{
	extern char	**environ;
	int			i;

	i = -1;
	while (environ && environ[++i])
		printf("%s\n", environ[i]);
	if (!environ || i == 0)
		printf("No environment variables!\n");
}

void	ft_free_environ(void)
{
	extern char	**environ;
	int			i;

	i = -1;
	while (environ && environ[++i])
		free(environ[i]);
	free(environ);
	environ = NULL;
}