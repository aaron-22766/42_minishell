#include "minishell.h"

static void	ft_puterror(const char *fault)
{
	ft_printf("minishell: %s\n", fault);
}

void	ft_perror(int err)
{
	if (err == ERR_MEM)
		ft_puterror("Memory allocation failed!");
}
