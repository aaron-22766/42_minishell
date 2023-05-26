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

// remove dumb_builtins function when builtins can be used
void	dumb_builtins(char *line)
{
	char	**args;
	int		i;

	if (!ft_strcmp(line, "exit"))
	{
		free(line);
		ft_free_environ();
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strcmp(line, "env"))
		ft_print_environ();
	else
	{
		args = ft_split(line, ' ');
		if (!ft_strcmp(args[0], "export"))
			ft_putenv(args[1]);
		else if (!ft_strcmp(args[0], "unset"))
			ft_unsetenv(args[1]);
		else if (!ft_strcmp(args[0], "getenv"))
			printf("%s\n", getenv(args[1]));
		else
			system(line);
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
	}
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
		if (line[0])
			add_history(line);
		dumb_builtins(line);
		// execute(evaluate(parse(lex(line))));
		free(line);
	}
}
