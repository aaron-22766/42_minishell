#include "../../include/minishell/builtin.h"

static int	is_sorted(char **env)
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

static char	**ft_sort_env(void)
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

static void	ft_print_exp(char **env_sort)
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

int	ft_export(t_cmds *cmd)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (!cmd->argv[i])
		ft_print_exp(ft_sort_env());
	while (cmd->argv[i])
	{
		if (!ft_isalpha(cmd->argv[i][0]) && cmd->argv[i][0] != '_')
		{
			ft_eprintf("minishell: export: `%s': not a valid identifier\n",
				cmd->argv[i]);
			status = 1;
		}
		else
			ft_putenv(cmd->argv[i]);
		i++;
	}
	return (status);
}
