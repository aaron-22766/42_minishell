#include "minishell.h"

static void	ft_welcome_shell(void)
{
	char	*user;

	user = getenv("USER");
	printf("\n*****************************************\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\t\t\033[1;34mMINISHELL\033[0m\t\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*\tby @arabenst & @rhortens\t*\n");
	printf("*\t\t\t\t\t*\n");
	printf("*****************************************\n");
	printf("current user is: \033[1;32m@%s\033[0m\n\n", user);
}

void	ft_run_shell(void)
{
	char	*line;

	ft_welcome_shell();
	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			line = ft_strdup("exit");
		if (!ft_strcmp(line, "exit"))
		{
			// remove this if block when exit builtin can be run instead
			free(line);
			ft_free_environ();
			exit(EXIT_SUCCESS);
		}
		if (line[0])
			add_history(line);
		// execute(evaluate(parse(lex(line))));
		if (!ft_strcmp(line, "env")) // remove this if block when env builtin can be run instead
			ft_print_environ();
		else
			system(line);
		free(line);
	}
}
