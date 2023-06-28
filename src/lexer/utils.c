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

t_tokens	*print_tokens(t_tokens *tokens, const char *title)
{
	if (title)
		printf("\e[1;33m%s\e[0m\n", title);
	if (!tokens)
		printf("No tokens\n");
	while (tokens)
	{
		if (tokens->id == WORD)
			printf("[WORD] ");
		else if (tokens->id == IN_FILE)
			printf("[IN_FILE] ");
		else if (tokens->id == OUT_FILE)
			printf("[OUT_FILE] ");
		else if (tokens->id == HEREDOC_EOF)
			printf("[HEREDOC_EOF] ");
		else if (tokens->id == OUT_A_FILE)
			printf("[OUT_A_FILE] ");
		else if (tokens->id == COMMAND)
			printf("[COMMAND] ");
		else if (tokens->id == OPERATOR)
			printf("[OPERATOR] ");
		else if (tokens->id == IN_RED)
			printf("[IN_RED] ");
		else if (tokens->id == OUT_RED)
			printf("[OUT_RED] ");
		else if (tokens->id == HEREDOC)
			printf("[HEREDOC] ");
		else if (tokens->id == OUT_A_RED)
			printf("[OUT_A_RED] ");
		else if (tokens->id == PIPE)
			printf("[PIPE] ");
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
	return (tokens);
}
