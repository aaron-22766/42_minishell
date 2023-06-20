#include "../../include/minishell/parser.h"

static void	ft_remove_quotes(t_tokens *tokens)
{
	size_t	i;
	char	quote;

	while (tokens)
	{
		quote = 0;
		i = -1;
		while (tokens->content[++i])
		{
			if (!quote && ft_strchr("\'\"", tokens->content[i]))
				quote = tokens->content[i];
			else if (tokens->content[i] == quote)
				quote = 0;
			else
				continue ;
			ft_strcpy(&tokens->content[i], &tokens->content[i + 1]);
			i--;
		}
		tokens = tokens->next;
	}
}

t_cmds	*ft_parse(unsigned char status, t_tokens *tokens)
{
	t_cmds	*commands;

	if (verbose)
		print_tokens(tokens, "TOKENS");
	if (!tokens || ft_expand_tokens(status, &tokens) == RETURN_FAILURE
		|| !tokens)
		return (ft_free_tokens(tokens), NULL);
	ft_evaluate_commands(tokens);
	ft_remove_quotes(tokens);
	if (verbose)
		print_tokens(tokens, "EXPANDED TOKENS");
	commands = ft_create_commands(tokens);
	if (!commands)
		return (ft_free_tokens(tokens), NULL);
	return (commands);
}
