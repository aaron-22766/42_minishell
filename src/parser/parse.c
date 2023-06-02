#include "../../include/minishell/parser.h"

t_cmds	*ft_parse(t_tokens *tokens)
{
	if (!tokens)
		return (NULL);
	if (ft_expand_tokens(tokens) == RETURN_FAILURE)
		return (ft_free_tokens(tokens), NULL);
	if (verbose)
	{
		printf("\033[1;33mTOKENS\033[0m\n");
		print_tokens(tokens);
	}
	ft_free_tokens(tokens);
	return (NULL);
}
