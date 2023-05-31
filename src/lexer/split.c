#include "../../include/minishell/lexer.h"

static char	ft_split_token(t_tokens *token, size_t start)
{
	t_tokens	*new;

	new = ft_new_token(ft_substr(token->content, start,
				ft_strlen(&token->content[start])));
	if (!new)
		return (RETURN_FAILURE);
	new->next = token->next;
	token->next = new;
	token->content[start] = '\0';
	return (RETURN_SUCCESS);
}

static char	ft_try_split(t_tokens *token)
{
	size_t	index;

	index = ft_unquoted_char(token->content, "<>|", "\'\"");
	if (!token->content[index])
		return (RETURN_SUCCESS);
	if (index)
		return (ft_split_token(token, index));
	index += 1 + (ft_strchr("<>", token->content[index])
			&& token->content[index] == token->content[index + 1]);
	if (!token->content[index])
		return (RETURN_SUCCESS);
	return (ft_split_token(token, index));
}

char	ft_split_at_operators(t_tokens *tokens)
{
	while (tokens)
	{
		if (ft_try_split(tokens) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		tokens = tokens->next;
	}
	return (RETURN_SUCCESS);
}
