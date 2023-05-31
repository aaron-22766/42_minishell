#include "../../include/minishell/lexer.h"

t_tokens	*ft_new_token(char *content)
{
	t_tokens	*new;

	if (!content)
		return (ft_perror(ERR_MEM, "creating token content"), NULL);
	new = malloc(sizeof(t_tokens));
	if (!new)
		return (ft_perror(ERR_MEM, "creating token"), free(content), NULL);
	new->id = WORD;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_free_tokens(t_tokens *tokens)
{
	t_tokens	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

size_t	ft_unquoted_char(char *str, const char *chars, const char *quotes)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && ft_strchr(chars, str[i]))
			break ;
		if (!quote && ft_strchr(quotes, str[i]))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (i);
}

// remove on final
t_tokens	*print_tokens(t_tokens *tokens)
{
	if (!tokens)
		printf("No tokens\n");
	while (tokens)
	{
		if (tokens->id == WORD)
			printf("[WORD] ");
		else if (tokens->id == OPERATOR)
			printf("[OPERATOR] ");
		else if (tokens->id == WORD)
			printf("[WORD] ");
		else if (tokens->id == COMMAND)
			printf("[COMMAND] ");
		else if (tokens->id == FILE_NAME)
			printf("[FILE_NAME] ");
		else if (tokens->id == HEREDOC_EOF)
			printf("[HEREDOC_EOF] ");
		else if (tokens->id == OPERATOR)
			printf("[OPERATOR] ");
		else if (tokens->id == I_RED)
			printf("[I_RED] ");
		else if (tokens->id == O_RED)
			printf("[O_RED] ");
		else if (tokens->id == O_RED_A)
			printf("[O_RED_A] ");
		else if (tokens->id == HEREDOC)
			printf("[HEREDOC] ");
		else if (tokens->id == PIPE)
			printf("[PIPE] ");
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}
