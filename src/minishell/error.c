#include "../../include/minishell/minishell.h"

// static void	ft_puterror(const char *fault)
// {
	
// }

void	ft_perror(int err, char *context)
{
	if (err)
		ft_printf("minishell: ");
	if (err == ERR_MEM)
		ft_printf("memory allocation failed while %s\n", context);
}
