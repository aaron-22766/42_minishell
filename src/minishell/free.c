#include "../../include/minishell/minishell.h"

void	ft_free_commands(t_cmds *commands)
{
	t_cmds	*next;

	while (commands)
	{
		next = commands->next;
		free(commands);
		commands = next;
	}
}
