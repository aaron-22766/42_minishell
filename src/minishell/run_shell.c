#include "../../include/minishell/minishell.h"

static void	ft_welcome_shell(void)
{
	char	*user;

	user = getenv("USER");
	printf("\n*****************************************\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\t\t\e[1;34mMINISHELL\e[0m\t\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\tby @arabenst & @rhortens\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*****************************************\n");
	printf("current user is: \e[1;32m@%s\e[0m\n\n", user);
}

// remove dumb_builtins function when builtins can be used
void	dumb_builtins(char *line)
{
	char	**args;
	int		i;

	if (!ft_strcmp(line, "exit"))
	{
		free(line);
		ft_free_environ();
		system("leaks minishell");
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(line, "env"))
		ft_print_environ();
	else
	{
		args = ft_split(line, ' ');
		if (args && args[0] && !ft_strcmp(args[0], "export"))
			ft_putenv(args[1]);
		else if (args && args[0] && !ft_strcmp(args[0], "unset"))
			ft_unsetenv(args[1]);
		else if (args && args[0] && !ft_strcmp(args[0], "getenv"))
			printf("%s\n", getenv(args[1]));
		// else
		// 	system(line);
		i = -1;
		while (args && args[++i])
			free(args[i]);
		free(args);
	}
}

void	ft_run_shell(void)
{
	unsigned char	status;
	char			*prompt;
	char			*line;

	status = 0;
	ft_welcome_shell();
	while (true)
	{
		// prompt = ft_get_prompt(getenv("PS1"));
		prompt = "minishell> ";
		signal(SIGINT, ft_readline_handler);
		line = readline(prompt);
		signal(SIGINT, ft_sig_handler);
		if (!line)
		{
			ft_printf("\033[A\033[K%sexit\n", prompt);
			exit(0);
		}
		if (line[0])
		{
			add_history(line);
			dumb_builtins(line);
			status = ft_execute(status, ft_parse(status, ft_lex(line)));
		}
		free(line);
	}
}
