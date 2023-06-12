#include "../../include/minishell/parser.h"

static void	ft_expand_tilde(char **cont, size_t t)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*cont)[t] != '~')
		return ;
	if (getenv("HOME") && ((*cont)[t + 1] == '\0' || (*cont)[t + 1] == '/'))
		ft_insert_val(cont, getenv("HOME"), t, 1);
	else if (getenv("PWD") && (*cont)[t + 1] == '+'
		&& ((*cont)[t + 2] == '\0' || (*cont)[t + 2] == '/'))
		ft_insert_val(cont, getenv("PWD"), t, 2);
	else if (getenv("OLDPWD") && (*cont)[t + 1] == '-'
		&& ((*cont)[t + 2] == '\0' || (*cont)[t + 2] == '/'))
		ft_insert_val(cont, getenv("OLDPWD"), t, 2);
	else if ((*cont)[t + 1])
	{
		end = ft_setchar(*cont + t, '\0', ft_strchr_index(*cont + t, '/'));
		ft_asprintf(&path, "/Users/%s", *cont + t + 1);
		end = ft_setchar(*cont + t, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			ft_insert_val(cont, path, t, end);
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

static char	ft_replace_var(char id, char **content, size_t start, size_t len)
{
	char	*val;
	char	temp;

	if ((*content)[start + 1] == '?')
	{
		val = ft_itoa(-42);//real exit status
		if (val)
			ft_insert_val(content, val, start, len);
		free(val);
		return (RETURN_SUCCESS);
	}
	temp = (*content)[start + len];
	(*content)[start + len] = '\0';
	val = getenv(&(*content)[start + 1]);
	if (start == 0 && len == ft_strlen(*content) && !val)
	{
		if (id == IN_FILE || id == OUT_FILE || id == OUT_A_FILE)
			return (ft_perror(ERR_AMBIG_RED, *content), RETURN_FAILURE);
		return (RMV);
	}
	(*content)[start + len] = temp;
	ft_insert_val(content, val, start, len);
	return (RETURN_SUCCESS);
}

char	ft_expand_env_vars(char **content, char *quotes, char id)
{
	size_t	start;
	size_t	len;
	char	ret;

	start = ft_unquoted_char(*content, "$", quotes);
	while ((*content)[start])
	{
		len = 1;
		ret = RETURN_SUCCESS;
		if (ft_isalpha((*content)[start + 1]) || (*content)[start + 1] == '_')
		{
			while (ft_isalnum((*content)[start + len])
				|| (*content)[start + len] == '_')
				len++;
			if (len > 1)
				ret = ft_replace_var(id, content, start, len);
		}
		else if ((*content)[start + 1] == '?')
			ret = ft_replace_var(id, content, start, 2);
		if (ret != RETURN_SUCCESS)
			return (ret);
		start += len + ft_unquoted_char(*content + start + len, "$", quotes);
	}
	return (RETURN_SUCCESS);
}

char	ft_expand_tokens(t_tokens **tokens)
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
			ret = ft_expand_env_vars(&current->content, "\'", current->id);
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
