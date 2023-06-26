#include "../../include/minishell/builtin.h"

static void	ft_print_var(char *var)
{
	size_t	i;

	if (!ft_strchr(var, '='))
	{
		printf("declare -x %s\n", var);
		return ;
	}
	printf("declare -x ");
	i = 0;
	while (var[i] && var[i] != '=')
		printf("%c", var[i++]);
	printf("=\"");
	while (var[++i])
	{
		if (var[i] == '\\')
			printf("\\");
		printf("%c", var[i]);
	}
	printf("\"\n");
}

char	ft_print_export(void)
{
	extern char	**environ;
	char		*prev;
	char		*current;
	size_t		i;
	size_t		j;

	if (!environ)
		return (1);
	prev = "";
	i = -1;
	while (environ[++i])
	{
		current = NULL;
		j = -1;
		while (environ[++j])
		{
			if (ft_strcmp(environ[j], prev) > 0
				&& (!current || ft_strcmp(environ[j], current) < 0))
				current = environ[j];
		}
		if (!!ft_strncmp(current, "_=", 2))
			ft_print_var(current);
		prev = current;
	}
	return (0);
}

int	ft_export(t_cmds *cmd)
{
	int		status;
	size_t	i;

	if (cmd->argv[1][0] == '-')
		return (ft_eprintf("minishell: export: -%c: invalid option\n",
				cmd->argv[1][1]), 2);
	status = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_valid_identifier(cmd->argv[i], '=') == false)
		{
			ft_eprintf("minishell: export: `%s': not a valid identifier\n",
				cmd->argv[i]);
			status = 1;
		}
		else
			if (ft_putenv(cmd->argv[i]) == -1)
				ft_eprintf("minishell: export: `%s': failed to export\n",
					cmd->argv[i]);
		i++;
	}
	return (status);
}
