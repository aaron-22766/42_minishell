#include "../../include/minishell/parser.h"

static size_t	ft_count_argv_tokens(t_tokens *tokens)
{
	size_t	count;

	count = 0;
	while (tokens && tokens->id != PIPE)
	{
		if (tokens->id == COMMAND || tokens->id == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static t_cmds	*ft_new_cmd(size_t argvs)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->path = NULL;
	new->argv = NULL;
	new->io_red = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->builtin = B_NO;
	new->next = NULL;
	if (argvs)
		new->argv = ft_calloc(argvs + 1, sizeof(char *));
	if (argvs && !new->argv)
		return (free(new), NULL);
	return (new);
}

t_cmds	*ft_allocate_command_table(t_tokens *tokens)
{
	t_cmds	*commands;
	t_cmds	*last;

	commands = ft_new_cmd(ft_count_argv_tokens(tokens));
	last = commands;
	while (last)
	{
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (!tokens)
			return (commands);
		tokens = tokens->next;
		last->next = ft_new_cmd(ft_count_argv_tokens(tokens));
		last = last->next;
	}
	return (ft_free_cmds(commands), NULL);
}
