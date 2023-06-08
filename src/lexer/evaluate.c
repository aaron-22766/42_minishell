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

static char	*ft_evaluate_words(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	while (temp && temp->next)
	{
		if (temp->id & OPERATOR && temp->id != PIPE
			&& temp->next->id & OPERATOR)
			return (temp->next->content);
		if (temp->id == I_RED || temp->id == O_RED || temp->id == O_RED_A)
			temp->next->id = FILE_NAME;
		else if (temp->id == HEREDOC)
			temp->next->id = HEREDOC_EOF;
		temp = temp->next;
	}
	while (tokens)
	{
		while (tokens && tokens->id != WORD)
			tokens = tokens->next;
		if (!tokens)
			return (NULL);
		tokens->id = COMMAND;
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
	}
	return (NULL);
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
	err_context = ft_evaluate_words(tokens);
	if (err_context)
		return (ft_perror(ERR_TOKEN_SYNTAX, err_context), RETURN_FAILURE);
	err_context = ft_check_syntax(tokens);
	if (err_context)
		return (ft_perror(ERR_TOKEN_SYNTAX, err_context), RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
