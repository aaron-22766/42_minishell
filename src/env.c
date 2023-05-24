#include "minishell.h"

void	ft_free_environ(void)
{
	extern char	**environ;
	int			i;

	i = -1;
	while (environ && environ[++i])
	{
		free(environ[i]);
		environ[i] = NULL;
	}
	free(environ);
	environ = ft_calloc(1, sizeof(char *));
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

bool	ft_is_env_var(const char *var1, const char *var2, size_t name_len)
{
	if (name_len < 1 || ft_strlen(var1) < name_len + 2)
		return (false);
	return (!ft_strncmp(var1, var2, name_len)
		&& var1[name_len] == '=');
}

static void	ft_realloc_environ(size_t size, const char *unset)
{
	extern char	**environ;
	char		**new;
	int			i;
	int			n;

	new = ft_calloc(size + 1, sizeof(char *));
	if (new)
	{
		n = 0;
		i = -1;
		while (environ && environ[++i])
			if (!ft_is_env_var(environ[i], unset, ft_strlen(unset)))
				new[n++] = environ[i];
	}
	ft_free_environ();
	free(environ);
	environ = new;
}

static char	*ft_join_env_var(const char *name, const char *value)
{
	char	*var;
	size_t	size;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	var = ft_calloc(size, sizeof(char));
	if (!var)
		return (NULL);
	ft_strcpy(var, name);
	ft_strlcat(var, "=", size);
	ft_strlcat(var, value, size);
	return (var);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	extern char	**environ;
	int			size;
	int			exists;

	exists = -1;
	size = -1;
	while (environ && environ[++size])
		if (ft_is_env_var(environ[size], name, ft_strlen(name)))
			exists = size;
	if (exists == -1)
	{
		ft_realloc_environ(size + 1, NULL);
		if (!environ)
			return (-1);
		environ[size] = ft_join_env_var(name, value);
		return (-1 * !environ[size]);
	}
	if (overwrite)
	{
		free(environ[exists]);
		environ[exists] = ft_join_env_var(name, value);
	}
	return (0);
}

int	ft_putenv(char *string)
{
	extern char	**environ;
	int			size;
	int			exists;

	exists = -1;
	size = -1;
	while (environ[++size])
		if (ft_is_env_var(environ[size], string, ft_strchr_index(string, '=')))
			exists = size;
	if (exists == -1)
	{
		ft_realloc_environ(size + 1, NULL);
		environ[size] = ft_strdup(string);
		return (-1 * !environ[size]);
	}
	free(environ[exists]);
	environ[exists] = ft_strdup(string);
	return (0);
}

int	ft_unsetenv(const char *name)
{
	extern char	**environ;
	int			size;

	size = 0;
	while (environ[size])
		size++;
	ft_realloc_environ(size - 1, name);
	return (!!environ);
}
