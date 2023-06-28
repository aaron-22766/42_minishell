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

static void	ft_set_verbose(int argc, char **argv)
{
	int	i;

	verbose = false;
	i = 0;
	while (++i < argc)
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			verbose = true;
}

static void	ft_configure_terminal(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

static void	ft_welcome_shell(void)
{
	printf("\n*****************************************\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\t\t\e[1;34mMINISHELL\e[0m\t\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\tby @arabenst & @rhortens\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*****************************************\n");
	printf("current user is: \e[1;32m@%s\e[0m\n\n", getenv("USER"));
}

int	main(int argc, char **argv)
{
	signal(SIGQUIT, SIG_IGN);
	ft_set_verbose(argc, argv);
	ft_init_shell(argv[0]);
	ft_configure_terminal();
	ft_welcome_shell();
	return (ft_run_shell(0, 0));
}
