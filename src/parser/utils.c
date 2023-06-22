#include "../../include/minishell/parser.h"

void	ft_free_cmds(t_cmds *commands)
{
	t_cmds	*next;
	size_t	i;

	while (commands)
	{
		free(commands->path);
		i = -1;
		while (commands->argv && commands->argv[++i])
			free(commands->argv[i]);
		free(commands->argv);
		ft_free_tokens(commands->io_red);
		next = commands->next;
		free(commands);
		commands = next;
	}
}

ssize_t	ft_setchar(char *str, char c, ssize_t index)
{
	if (c == '/' && index < 0)
		return (ft_strlen(str));
	if (!str || index < 0 || index > (ssize_t)ft_strlen(str))
		return (-1);
	str[index] = c;
	return (index);
}

t_tokens	*ft_remove_token(t_tokens **head, t_tokens *remove)
{
	t_tokens	*current;
	t_tokens	*prev;

	current = *head;
	if (current == remove)
	{
		*head = current->next;
		free(current->content);
		free(current);
		return (*head);
	}
	while (current && current != remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (NULL);
	prev->next = current->next;
	free(current->content);
	free(current);
	return (prev->next);
}

void	print_cmds(t_cmds *commands)
{
	size_t	i;

	printf("\e[1;33mCOMMANDS\e[0m\n");
	if (!commands)
		printf("No commands\n");
	while (commands)
	{
		printf("PATH: %s\n", commands->path);
		printf("ARGS:");
		i = -1;
		while (commands->argv && commands->argv[++i])
			printf("[%s]", commands->argv[i]);
		printf("\nREDIRECTIONS:\n");
		print_tokens(commands->io_red, NULL);
		printf("fd_in: %d\nfd_out: %d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\e[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\e[0m\n");
	}
}
