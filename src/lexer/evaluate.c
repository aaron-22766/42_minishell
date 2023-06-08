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

static char	*ft_evaluate_redrections(t_tokens *tokens)
{
	while (tokens && tokens->next)
	{
		if (tokens->id & OPERATOR && tokens->id != PIPE
			&& tokens->next->id & OPERATOR)
			return (tokens->next->content);
		if (tokens->id == I_RED || tokens->id == O_RED || tokens->id == O_RED_A)
			tokens->next->id = FILE_NAME;
		else if (tokens->id == HEREDOC)
			tokens->next->id = HEREDOC_EOF;
		tokens = tokens->next;
	}
	return (NULL);
}

void	ft_evaluate_commands(t_tokens *tokens)
{
	while (tokens)
	{
		while (tokens && tokens->id != WORD && tokens->id != COMMAND)
			tokens = tokens->next;
		if (!tokens)
			return ;
		tokens->id = COMMAND;
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
	}
}

static char	*ft_check_syntax(t_tokens *tokens)
{
	size_t	i;
	char	quote;

	if (tokens->id == PIPE)
		return (tokens->content);
	while (tokens->next)
		tokens = tokens->next;
	if (tokens->id & OPERATOR)
		return ("newline");
	quote = 0;
	i = 0;
	while (tokens->content[i])
	{
		if (!quote && ft_strchr("\'\"", tokens->content[i]))
			quote = tokens->content[i];
		else if (tokens->content[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (tokens->content);
	return (NULL);
}

char	ft_evaluate_tokens(t_tokens *tokens)
{
	char	*err_context;

	ft_evaluate_operators(tokens);
	err_context = ft_evaluate_redrections(tokens);
	if (err_context)
		return (ft_perror(ERR_TOKEN_SYNTAX, err_context), RETURN_FAILURE);
	ft_evaluate_commands(tokens);
	err_context = ft_check_syntax(tokens);
	if (err_context)
		return (ft_perror(ERR_TOKEN_SYNTAX, err_context), RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
