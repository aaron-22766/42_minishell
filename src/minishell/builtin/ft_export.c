#include "../../../include/minishell/builtin.h"

int	is_sorted(char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i] && env[i + 1])
	{
		j = 0;
		while (env[i][j] && env[i + 1][j] && env[i][j] == env[i + 1][j])
			j++;
		if (env[i][j] > env[i + 1][j])
			return (0);
		i++;
	}
	return (1);
}

char	**ft_sort_env(void)
{
	extern char	**environ;
	char		*tmp;
	int			i;
	int			j;

	while (!is_sorted(environ))
	{
		i = 0;
		while (environ[i] && environ[i + 1])
		{
			j = 0;
			while (environ[i][j] == environ[i + 1][j])
				j++;
			if (environ[i][j] > environ[i + 1][j])
			{
				tmp = environ[i];
				environ[i] = environ[i + 1];
				environ[i + 1] = tmp;
			}
			i++;
		}
	}
	return (environ);
}

void	ft_print_exp(char **env_sort)
{
	char		*equal;
	int			i;
	int			n;

	i = 0;
	while (env_sort[i])
	{
		equal = ft_strchr(env_sort[i], '=');
		if (equal != NULL && env_sort[i][1] != '=')
		{
			n = (int)(equal - env_sort[i]);
			printf("declare -x %.*s=\"%s\"\n", n, env_sort[i],
				env_sort[i] + n + 1);
		}
		else if (env_sort[i][1] != '=')
			printf("declare -x %s\n", env_sort[i]);
		i++;
	}
}

int	ft_check_var(t_cmds *command, char *cmd)
{
	int	i;

	(void) command;
	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
	{
		printf("minishell: export: '%s': not a valid identifier\n", cmd);
		return (-1);
	}
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '=')
	{
		if (cmd[i + 1] == '\0')
			return (0);
		return (0);
	}
	return (0);
}

void	ft_export(t_cmds *command)
{
	int	i;
	int	check_exp;

	i = 1;
	if (!command->argv[i])
		ft_print_exp(ft_sort_env());
	while (command->argv[i])
	{
		check_exp = ft_check_var(command, command->argv[i]);
		if (check_exp != -1)
			ft_putenv(command->argv[i]);
		i++;
	}
}
