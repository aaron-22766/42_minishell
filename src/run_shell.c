#include "minishell.h"

void	ft_run_shell(void)
{
	char	*line;

	while (true)
	{
		line = readline("minishell> ");
		if (!line || !ft_strcmp(line, "exit"))
		{
			// remove strcmp and free(line) so exit builtin will be executed
			free(line);
			// rl_replace_line("exit", 0);
			// rl_redisplay();
			ft_free();
			exit(EXIT_SUCCESS);
		}
		if (line[0])
			add_history(line);
		system(line);
		free(line);
	}
}
