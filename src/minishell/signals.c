#include "../../include/minishell/minishell.h"

void	ft_readline_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	ft_sig_handler(int sig)
{
	g_ctrlc = true;
	(void)sig;
}
