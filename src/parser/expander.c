#include "../../include/minishell/parser.h"

static void	ft_expand_tilde(char **cont, size_t t)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*cont)[t] != '~')
		return ;
	if (getenv("HOME") && ((*cont)[t + 1] == '\0' || (*cont)[t + 1] == '/'))
		ft_str_insert(cont, getenv("HOME"), t, 1);
	else if (getenv("PWD") && (*cont)[t + 1] == '+'
		&& ((*cont)[t + 2] == '\0' || (*cont)[t + 2] == '/'))
		ft_str_insert(cont, getenv("PWD"), t, 2);
	else if (getenv("OLDPWD") && (*cont)[t + 1] == '-'
		&& ((*cont)[t + 2] == '\0' || (*cont)[t + 2] == '/'))
		ft_str_insert(cont, getenv("OLDPWD"), t, 2);
	else if ((*cont)[t + 1])
	{
		end = ft_setchar(*cont + t, '\0', ft_strchr_index(*cont + t, '/'));
		ft_asprintf(&path, "/Users/%s", *cont + t + 1);
		end = ft_setchar(*cont + t, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			ft_str_insert(cont, path, t, end);
		free(path);
	}
}

static void	ft_expand_assignment_tilde(char **content)
{
	size_t	i;

	i = 0;
	while (ft_isalnum((*content)[i]) || (*content)[i] == '_')
		i++;
	if (i && (*content)[i] == '=')
		ft_expand_tilde(content, i + 1);
}

static char	ft_replace_var(unsigned char status, char id, char **content,
			size_t var[2])
{
	char	*val;
	char	temp;

	if ((*content)[var[0] + 1] == '?')
	{
		val = ft_itoa(status);
		if (val)
			ft_str_insert(content, val, var[0], var[1]);
		free(val);
		return (RETURN_SUCCESS);
	}
	temp = (*content)[var[0] + var[1]];
	(*content)[var[0] + var[1]] = '\0';
	val = getenv(&(*content)[var[0] + 1]);
	if (var[0] == 0 && var[1] == ft_strlen(*content) && !val)
	{
		if (id == IN_FILE || id == OUT_FILE || id == OUT_A_FILE)
			return (ft_perror(ERR_AMBIG_RED, *content), RETURN_FAILURE);
		return (RMV);
	}
	(*content)[var[0] + var[1]] = temp;
	ft_str_insert(content, val, var[0], var[1]);
	return (RETURN_SUCCESS);
}

char	ft_expand_env_vars(unsigned char status, char **content, char *quotes,
		char id)
{
	size_t	var[2];
	char	ret;

	var[0] = ft_unquoted_char(*content, "$", quotes);
	while ((*content)[var[0]])
	{
		var[1] = 1;
		ret = RETURN_SUCCESS;
		if (ft_isalpha((*content)[var[0] + 1]) || (*content)[var[0] + 1] == '_')
		{
			while (ft_isalnum((*content)[var[0] + var[1]])
				|| (*content)[var[0] + var[1]] == '_')
				var[1]++;
			if (var[1] > 1)
				ret = ft_replace_var(status, id, content, var);
		}
		else if ((*content)[var[0] + 1] == '?' && var[1]++)
			ret = ft_replace_var(status, id, content, var);
		if (ret != RETURN_SUCCESS)
			return (ret);
		var[0] += var[1] + ft_unquoted_char(*content + var[0] + var[1],
				"$", quotes);
	}
	return (RETURN_SUCCESS);
}

char	ft_expand_tokens(unsigned char status, t_tokens **tokens)
{
	t_tokens	*current;
	char		ret;

	current = *tokens;
	while (current)
	{
		if (current->id & WORD && current->id != HEREDOC_EOF)
		{
			ft_expand_tilde(&current->content, 0);
			ft_expand_assignment_tilde(&current->content);
			ret = ft_expand_env_vars(status, &current->content,
					"\'", current->id);
			if (ret == RETURN_FAILURE)
				return (RETURN_FAILURE);
			else if (ret == RMV)
			{
				current = ft_remove_token(tokens, current);
				continue ;
			}
		}
		current = current->next;
	}
	return (RETURN_SUCCESS);
}
