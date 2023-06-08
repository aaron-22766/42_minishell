#include "../../include/minishell/parser.h"

static void	ft_tokens_to_command(t_tokens *tokens, t_cmds *command)
{
	size_t	argvs;
	size_t	heredocs;
	size_t	out_reds;

	argvs = 0;
	heredocs = 0;
	out_reds = 0;
	while (tokens && tokens->id != PIPE)
	{
		if (tokens->id == COMMAND || tokens->id == WORD)
			command->argv[argvs++] = tokens->content;
		else if (tokens->id == I_RED)
		{
			free(command->in_red);
			command->in_red = tokens->next->content;
		}
		else if (tokens->id == HEREDOC)
			command->heredoc[heredocs++] = tokens->next->content;
		else if (tokens->id == O_RED || tokens->id == O_RED_A)
		{
			command->out_red[out_reds++] = tokens->next->content;
			command->append = O_APPEND * (tokens->id == O_RED_A);
		}
		tokens = tokens->next;
	}
}

static void	ft_tokens_to_table(t_tokens *tokens, t_cmds *command)
{
	while (tokens)
	{
		ft_tokens_to_command(tokens, command);
		while (tokens && tokens->id != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
		command = command->next;
	}
}

static void	ft_free_operators(t_tokens *tokens)
{
	t_tokens	*next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->id & OPERATOR)
			free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

t_cmds	*ft_create_commands(t_tokens *tokens)
{
	t_cmds	*commands;
	t_cmds	*temp;

	commands = ft_allocate_command_table(tokens);
	if (!commands)
		return (ft_perror(ERR_MEM, "creating command table"), NULL);
	temp = commands;
	ft_tokens_to_table(tokens, commands);
	ft_free_operators(tokens);
	return (commands);
}
