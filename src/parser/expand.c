#include "../../include/minishell/parser.h"

static char	ft_expand_tilde(char **content)
{
	(void)content;
	return (RETURN_SUCCESS);
}

char	ft_expand_tokens(t_tokens *tokens)
{
	t_tokens	*prev;
	char		ret;

	prev = NULL;
	while (tokens)
	{
		if (tokens->id & WORD && tokens->id != HEREDOC_EOF)
		{
			ret = ft_expand_env_vars(&tokens->content, tokens->id);
			if (ret == RETURN_FAILURE)
				return (RETURN_FAILURE);
			else if (ret == RMV || ft_expand_tilde(&tokens->content) == RMV)
			{
				prev->next = token->next;
				free(tokens->content);
				free(tokens);
				tokens = prev;
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (RETURN_SUCCESS);
}
