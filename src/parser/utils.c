#include "../../include/minishell/parser.h"

void	ft_free_cmds(t_cmds *commands)
{
	t_cmds	*next;
	size_t	i;

	while (commands)
	{
		i = -1;
		while (commands->argv && commands->argv[++i])
			free(commands->argv[i]);
		free(commands->argv);
		free(commands->in_red);
		i = -1;
		while (commands->heredoc && commands->heredoc[++i])
			free(commands->heredoc[i]);
		free(commands->heredoc);
		i = -1;
		while (commands->out_red && commands->out_red[++i])
			free(commands->out_red[i]);
		free(commands->out_red);
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
		printf("ARG: ");
		i = -1;
		while (commands->argv && commands->argv[++i])
			printf("[%s]", commands->argv[i]);
		printf("\nIN : ");
		if (commands->in_red)
			printf("[%s]", commands->in_red);
		printf("\nHD : ");
		i = -1;
		while (commands->heredoc && commands->heredoc[++i])
			printf("[%s]", commands->heredoc[i]);
		printf("\nOUT: ");
		i = -1;
		while (commands->out_red && commands->out_red[++i])
			printf("[%s]", commands->out_red[i]);
		printf("\nAPP: %d\n", commands->append);
		commands = commands->next;
		if (commands)
			printf("\033[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\033[0m\n");
	}
}
