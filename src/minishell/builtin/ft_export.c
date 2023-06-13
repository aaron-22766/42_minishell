#include "../../../include/minishell/minishell.h"

void	ft_print_exp(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("declare -x %s\n", environ[i]);
		i++;
	}
}

char	ft_check_var(char *cmd)
{
	int	i;

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
			return (1);
		return (0);
	}
	return (-1);
}

char	ft_check_exp(t_cmds *command, char exp, int i)
{
	extern char	**environ;
	int			n;
	int			len;

	n = 0;
	len = 0;
	while (command->argv[i][len] != '\0')
		len++;
	while (environ[n])
	{
		if (!ft_strncmp(command->argv[i], environ[n], len)
			&& environ[n][len] == '=')
		{
			free(environ[n]);
			if (exp)
				environ[n] = ft_strjoin(command->argv[i], "\0");
			else
				environ[n] = ft_strdup(command->argv[i]);
			if (!environ[n])
				return (-1);
			return (1);
		}
		n++;
	}
	return (0);
}

void	ft_export(t_cmds *command)
{
	extern char	**environ;
	int			i;
	char		*check_exp;

	i = 1;
	if (!command->argv[i])
		ft_print_exp();
	while (command->argv[i])
	{
		check_exp = ft_check_var(command->argv[i]);
		if (check_exp != -1)
			check_exp = ft_check_exp(command, check_exp, i);
		i++;
	}
	ft_free_commands(command);
}
