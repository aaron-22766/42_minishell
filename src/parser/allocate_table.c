#include "../../include/minishell/parser.h"

static t_cmds	*ft_new_cmd(size_t argvs, size_t heredocs, size_t out_reds)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->in_red = NULL;
	new->heredoc = NULL;
	new->out_red = NULL;
	new->append = 0;
	new->next = NULL;
	if (argvs)
		new->argv = ft_calloc(argvs + 1, sizeof(char *));
	if (heredocs)
		new->heredoc = ft_calloc(heredocs + 1, sizeof(char *));
	if (out_reds)
		new->out_red = ft_calloc(out_reds + 1, sizeof(char *));
	if ((argvs && !new->argv) || (heredocs && !new->heredoc)
		|| (out_reds && !new->out_red))
		return (free(new->argv), free(new->heredoc),
			free(new->out_red), free(new), NULL);
	return (new);
}

static size_t	ft_count_token(t_tokens *tokens, char id)
{
	size_t	count;

	count = 0;
	while (tokens && tokens->id != PIPE)
	{
		if (tokens->id == id)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_cmds	*ft_allocate_command_table(t_tokens *tokens)
{
	t_cmds	*commands;
	t_cmds	*last;

	commands = ft_new_cmd(ft_count_token(tokens, COMMAND)
			+ ft_count_token(tokens, WORD), ft_count_token(tokens, HEREDOC),
			ft_count_token(tokens, O_RED) + ft_count_token(tokens, O_RED_A));
	last = commands;
	while (last)
	{
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (!tokens)
			return (commands);
		tokens = tokens->next;
		last->next = ft_new_cmd(ft_count_token(tokens, COMMAND)
				+ ft_count_token(tokens, WORD),
				ft_count_token(tokens, HEREDOC),
				ft_count_token(tokens, O_RED)
				+ ft_count_token(tokens, O_RED_A));
		last = last->next;
	}
	return (ft_free_cmds(commands), NULL);
}
