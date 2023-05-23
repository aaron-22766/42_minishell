#include "minishell.h"

static void	ft_free_commands(void)
{
	t_cmds	*next;

	while (g_data.commands)
	{
		next = g_data.commands->next;
		free(g_data.commands);
		g_data.commands = next;
	}
}

void	ft_free(void)
{
	ft_free_commands();
}
