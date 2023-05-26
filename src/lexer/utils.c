#include "../../include/minishell/lexer.h"

void	print_tokens(t_tokens *tokens)
{
	if (!tokens)
		printf("No tokens\n");
	while (tokens)
	{
		if (tokens->type == INVALID)
			printf("[INVALID] ");
		else if (tokens->type == COMMAND)
			printf("[COMMAND] ");
		else if (tokens->type == ARGUMENT)
			printf("[ARGUMENT] ");
		else if (tokens->type == I_RED)
			printf("[I_RED] ");
		else if (tokens->type == O_RED)
			printf("[O_RED] ");
		else if (tokens->type == HERE_DOC)
			printf("[HERE_DOC] ");
		else if (tokens->type == O_RED_A)
			printf("[O_RED_A] ");
		else if (tokens->type == PIPE)
			printf("[PIPE] ");
		else if (tokens->type == HD_EOF)
			printf("[HD_EOF] ");
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
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
