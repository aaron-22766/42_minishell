#include "../../include/minishell/minishell.h"

void	ft_perror(int err, char *context)
{
	ft_perror_exe("minishell", err, context);
}

void	ft_perror_exe(char *exe, int err, char *context)
{
	ft_printf("%s: ", exe);
	if (err == ERR_MEM)
		ft_printf("memory allocation failed while %s", context);
	else if (err == ERR_TOKEN_SYNTAX)
		ft_printf("syntax error near unexpected token `%s'", context);
	ft_printf("\n");
}
