#include "../../include/minishell/parser.h"

static void	ft_expand_tilde(char **str, size_t t)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*str)[t] != '~')
		return ;
	if (getenv("HOME") && ((*str)[t + 1] == '\0' || (*str)[t + 1] == '/'))
		ft_str_insert(str, getenv("HOME"), t, 1);
	else if (getenv("PWD") && (*str)[t + 1] == '+'
		&& ((*str)[t + 2] == '\0' || (*str)[t + 2] == '/'))
		ft_str_insert(str, getenv("PWD"), t, 2);
	else if (getenv("OLDPWD") && (*str)[t + 1] == '-'
		&& ((*str)[t + 2] == '\0' || (*str)[t + 2] == '/'))
		ft_str_insert(str, getenv("OLDPWD"), t, 2);
	else if ((*str)[t + 1])
	{
		end = ft_setchar(*str + t, '\0', ft_strchr_index(*str + t, '/'));
		ft_asprintf(&path, "/Users/%s", *str + t + 1);
		end = ft_setchar(*str + t, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			ft_str_insert(str, path, t, end);
		free(path);
	}
}

static void	ft_expand_assignment_tilde(char **str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha((*str)[i]))
		while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
			i++;
	if (i && (*str)[i] == '=')
		ft_expand_tilde(str, i + 1);
}

static t_tokens	*ft_remove_token(t_tokens **head, t_tokens *remove)
{
	t_tokens	*current;
	t_tokens	*prev;

	current = *head;
	if (current == remove)
	{
		*head = current->next;
		free(current->content);
		free(current);
		return (*head);
	}
	while (current && current != remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (NULL);
	prev->next = current->next;
	free(current->content);
	free(current);
	return (prev->next);
}

char	ft_expand_tokens(int status, t_tokens **tokens)
{
	t_tokens	*tok;
	char		ret;

	tok = *tokens;
	while (tok)
	{
		ret = RETURN_SUCCESS;
		if (tok->id & WORD && tok->id != HEREDOC_EOF)
		{
			ft_expand_tilde(&tok->content, 0);
			ft_expand_assignment_tilde(&tok->content);
			ret = ft_expand(&tok->content, status, tok->id);
			if (ret == RETURN_FAILURE)
				return (RETURN_FAILURE);
			else if (ret == RMV)
				tok = ft_remove_token(tokens, tok);
		}
		if (ret == RETURN_SUCCESS)
			tok = tok->next;
	}
	return (RETURN_SUCCESS);
}
