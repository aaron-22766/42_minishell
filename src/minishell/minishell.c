#include "../../include/minishell/minishell.h"

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

static void	test(void)
{
	ft_printf("branch");
}

int	main(int argc, char **argv)
{
	test();
	test();
	signal(SIGQUIT, SIG_IGN);
	ft_set_verbose(argc, argv);
	ft_init_shell(argv[0]);
	ft_configure_terminal();
	ft_run_shell();
	return (-1);
}
