#include "../../include/minishell/lexer.h"

static char	ft_check_quotes(char *content)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = 0;
	while (content[i])
	{
		if (!quote && ft_strchr("\'\"", content[i]))
			quote = content[i];
		else if (content[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

char	*ft_check_syntax(t_tokens *tokens)
{
	if (tokens->id == PIPE)
		return (tokens->content);
	while (tokens->next)
	{
		if ((tokens->id & OPERATOR) && (tokens->next->id & OPERATOR))
			return (tokens->next->content);
		tokens = tokens->next;
	}
	if (tokens->id & OPERATOR)
		return ("newline");
	if (ft_check_quotes(tokens->content) == RETURN_FAILURE)
		return (tokens->content);
	return (NULL);
}
