#include "../../include/minishell/minishell.h"

static char	ft_env_size_increment(void)
{
	extern char	**environ;
	char		**new;
	int			i;

	if (!environ)
		return (RETURN_FAILURE);
	new = ft_calloc(ft_environ_size() + 2, sizeof(char *));
	if (!new)
		return (RETURN_FAILURE);
	i = -1;
	while (environ[++i])
		new[i] = environ[i];
	free(environ);
	environ = new;
	return (RETURN_SUCCESS);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	extern char	**environ;
	char		*new_var;
	int			existing;

	if (!environ || !value || !name || !name[0] || ft_strchr(name, '='))
		return (-1);
	existing = ft_existing_env_var(name, ft_strlen(name));
	if (existing == -1 && !overwrite)
		return (0);
	if (ft_asprintf(&new_var, "%s=%s", name, value) == -1)
		return (-1);
	if (existing == -1)
	{
		if (ft_env_size_increment() == RETURN_FAILURE)
			return (free(new_var), -1);
		environ[ft_environ_size()] = new_var;
	}
	else if (overwrite)
	{
		free(environ[existing]);
		environ[existing] = new_var;
	}
	return (0);
}

int	ft_putenv(char *string)
{
	extern char	**environ;
	char		*new_var;
	int			existing;

	if (!environ || !string)
		return (-1);
	existing = ft_existing_env_var(string, ft_strchr_index(string, '='));
	if (existing != -1 && !ft_strchr(string, '='))
		return (0);
	new_var = ft_strdup(string);
	if (!new_var)
		return (-1);
	if (existing == -1)
	{
		if (ft_env_size_increment() == RETURN_FAILURE)
			return (free(new_var), -1);
		environ[ft_environ_size()] = new_var;
	}
	else
	{
		free(environ[existing]);
		environ[existing] = new_var;
	}
	return (0);
}

int	ft_unsetenv(const char *name)
{
	extern char	**environ;
	size_t		last_index;
	size_t		i;

	if (!environ || !name || !name[0] || ft_strchr(name, '='))
		return (-1);
	last_index = ft_environ_size() - 1;
	i = -1;
	while (environ[++i])
	{
		if (ft_is_env_var(environ[i], name, ft_strlen(name)))
		{
			free(environ[i]);
			if (i != last_index)
				environ[i] = environ[last_index];
			environ[last_index--] = NULL;
		}
	}
	return (0);
}
