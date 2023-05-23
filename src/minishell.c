#include "minishell.h"

void	ft_init_data(void)
{
	g_data.verbose = false;
	g_data.commands = NULL;
}

void	ft_set_verbose(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			g_data.verbose = true;
}

static void	ft_sighandler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig != SIGINT)
		return ;
	// ctrl-c = SIGINT -> display new prompt on new line
	// ctrl-\ = SIGQUIT -> ignored
}

static bool	ft_handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_sighandler;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		return (printf("\nERROR!\nFailed to set up signal handler\n\n"),
			RETURN_FAILURE);
	if (g_data.verbose)
		printf("Signals set up successfully.\n");
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	ft_init_data();
	ft_set_verbose(argc, argv);
	if (ft_handle_signal() == RETURN_SUCCESS)
	{
		ft_init_shell();
		ft_run_shell();
	}
	return (-1);
}
