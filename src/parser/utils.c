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
		if (commands->fd_in != STDIN_FILENO)
			close(commands->fd_in);
		if (commands->fd_out != STDOUT_FILENO)
			close(commands->fd_out);
		next = commands->next;
		free(commands);
		commands = next;
	}
}

void	print_cmds(t_cmds *commands)
{
	size_t	i;

	printf("\033[1;33mCOMMANDS\033[0m\n");
	if (!commands)
		printf("No commands\n");
	while (commands)
	{
		printf("PATH: %s\n", commands->path);
		printf("ARGS:\n");
		i = -1;
		while (commands->argv && commands->argv[++i])
			printf("[%s]", commands->argv[i]);
		printf("\nREDIRECTIONS:\n");
		print_tokens(commands->io_red, NULL);
		printf("fd_in: %d\nfd_out: %d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\033[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\033[0m\n");
	}
}
