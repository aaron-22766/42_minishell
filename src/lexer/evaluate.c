#include "../../include/minishell/lexer.h"

static void	ft_evaluate_operators(t_tokens *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "<"))
			tokens->id = I_RED;
		else if (!ft_strcmp(tokens->content, ">"))
			tokens->id = O_RED;
		else if (!ft_strcmp(tokens->content, "<<"))
			tokens->id = HEREDOC;
		else if (!ft_strcmp(tokens->content, ">>"))
			tokens->id = O_RED_A;
		else if (!ft_strcmp(tokens->content, "|"))
			tokens->id = PIPE;
		tokens = tokens->next;
	}
}

static void	ft_evaluate_words(t_tokens *tokens)
{
	if (tokens->id & WORD)
		tokens->id = COMMAND;
	while (tokens && tokens->next)
	{
		if (tokens->id & WORD && tokens->id != WORD)
			tokens = tokens->next;
		while (tokens && tokens->next && tokens->next->id & OPERATOR)
			tokens = tokens->next;
		if (!tokens || !tokens->next)
			return ;
		if (tokens->id == I_RED || tokens->id == O_RED || tokens->id == O_RED_A)
			tokens->next->id = FILE_NAME;
		else if (tokens->id == HEREDOC)
			tokens->next->id = HEREDOC_EOF;
		else if (tokens->id == PIPE)
			tokens->next->id = COMMAND;
		tokens = tokens->next;
	}
}

void	ft_evaluate_tokens(t_tokens *tokens)
{
	ft_evaluate_operators(tokens);
	ft_evaluate_words(tokens);
}
