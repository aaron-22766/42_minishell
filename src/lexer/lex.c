#include "../../include/minishell/lexer.h"

t_tokens	*ft_new_token(char *content)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (ft_perror(ERR_MEM, "creating token"), NULL);
	new->type = INVALID;
	new->content = content;
	new->next = NULL;
	return (new);
}

t_tokens	*ft_evaluate_tokens(t_tokens *tokens)
{
	print_tokens(tokens);
	ft_free_tokens(tokens);
	return (NULL);
}

t_tokens	*ft_lex(char *line)
{
	t_tokens	*tokens;
	t_tokens	*last;
	char		**raw_tokens;
	size_t		i;

	raw_tokens = ft_split(line, ' '); // dont split "     " !!! -> strtok
	free(line);
	if (!raw_tokens)
		return (ft_perror(ERR_MEM, "splitting the line"), NULL);
	if (!raw_tokens[0])
		return (free(raw_tokens), NULL);
	tokens = ft_new_token(raw_tokens[0]);
	if (!tokens)
		return (ft_free_2d_array((void **)raw_tokens), NULL);
	last = tokens;
	i = 0;
	while (raw_tokens && raw_tokens[++i])
	{
		last->next = ft_new_token(raw_tokens[i]);
		last = last->next;
		if (!last)
			return (ft_free_tokens(tokens), NULL);
	}
	return (free(raw_tokens), ft_evaluate_tokens(tokens));
}
