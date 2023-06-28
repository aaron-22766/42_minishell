#include "../../include/minishell/parser.h"

static size_t	ft_next_env(char *str, size_t env, char is_heredoc)
{
	static char	quote;
	char		backslash;

	backslash = 0;
	while (str[env + 1])
	{
		if (str[env] == '$' && !backslash && (is_heredoc || quote != '\'')
			&& (ft_isalnum(str[env + 1]) || ft_strchr("!#$&*-?@_", str[env + 1])
				|| (str[env + 1] == '\\' && str[env + 2] != '\\')
				|| (!is_heredoc && !quote && ft_strchr("\'\"", str[env + 1]))))
			return (env);
		if (!quote && ft_strchr("\'\"", str[env]))
			quote = str[env];
		else if (str[env] == quote)
			quote = 0;
		if (!backslash && str[env] == '\\')
			backslash = 1;
		else
			backslash = 0;
		env++;
	}
	quote = 0;
	return (env + 1);
}

static size_t	ft_env_len(char *str)
{
	size_t	len;

	if (ft_strchr("\'\"", str[1]))
		return (1);
	if (ft_isdigit(str[1]) || ft_strchr("!#$&*-?@\\", str[1]))
		return (2);
	len = 2;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

static char	*ft_env_val(char *var, size_t len, int status)
{
	char	temp;
	char	*env;

	if (ft_isdigit(var[0]) || ft_strchr("!#$&*-@_\\\'\"", var[0]))
		return (NULL);
	if (var[0] == '?')
		return (ft_itoa(status));
	temp = var[len];
	var[len] = '\0';
	env = getenv(var);
	var[len] = temp;
	if (env)
		return (ft_strdup(env));
	return (NULL);
}

static void	ft_escaping_backslashes(char **str, char is_heredoc)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*str)[++i + 1])
	{
		if (!quote && ft_strchr("\'\"", (*str)[i]))
			quote = (*str)[i];
		else if ((*str)[i] == quote)
			quote = 0;
		if ((*str)[i] == '\\' && (is_heredoc || !quote))
			ft_str_insert(str, "", i, 1);
	}
}

char	ft_expand(char **str, int status, char id)
{
	size_t	env;
	size_t	len;
	char	*val;

	env = ft_next_env(*str, 0, id == HEREDOC);
	while ((*str)[env])
	{
		len = ft_env_len(*str + env);
		val = ft_env_val(*str + env + 1, len - 1, status);
		if (!val && env == 0 && len == ft_strlen(*str))
		{
			if (id == IN_FILE || id == OUT_FILE || id == OUT_A_FILE)
				return (ft_perror(ERR_AMBIG_RED, *str), RETURN_FAILURE);
			return (RMV);
		}
		if (ft_str_insert(str, val, env, len))
			env += ft_strplen(val);
		free(val);
		env = ft_next_env(*str, env, id == HEREDOC);
	}
	return (ft_escaping_backslashes(str, id == HEREDOC), RETURN_SUCCESS);
}
