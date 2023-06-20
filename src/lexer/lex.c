#include "../../include/minishell/lexer.h"

static char	*ft_get_next_token(char *str)
{
	static char	*cache;
	char		*tok;

	if (str)
		cache = str;
	while (cache && *cache && ft_strchr(" \n\t\r\v\f", *cache))
		cache++;
	if (!cache || !*cache)
		return (NULL);
	tok = cache;
	cache = &cache[ft_unquoted_char(cache, " \n\t\r\v\f", "\'\"")];
	if (*cache)
		*cache++ = '\0';
	return (tok);
}

static t_tokens	*ft_get_tokens(char *line)
{
	t_tokens	*tokens;
	t_tokens	*last;
	char		*tok;

	tok = ft_get_next_token(line);
	if (!tok)
		return (NULL);
	tokens = ft_new_token(ft_strdup(tok));
	if (!tokens)
		return (NULL);
	last = tokens;
	while (true)
	{
		tok = ft_get_next_token(NULL);
		if (!tok)
			break ;
		last->next = ft_new_token(ft_strdup(tok));
		last = last->next;
		if (!last)
			return (ft_free_tokens(tokens), NULL);
	}
	return (tokens);
}

t_tokens	*ft_lex(char *line)
{
	t_tokens	*tokens;

	tokens = ft_get_tokens(line);
	free(line);
	if (!tokens || ft_split_at_operators(tokens) == RETURN_FAILURE)
		return (ft_free_tokens(tokens), NULL);
	if (ft_evaluate_tokens(tokens) == RETURN_FAILURE)
		return (ft_free_tokens(tokens), NULL);
	return (tokens);
}
