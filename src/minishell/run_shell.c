#include "../../include/minishell/minishell.h"

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

static char	ft_only_space(char *line)
{
	size_t	i;

	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (false);
	return (true);
}

static char	*ft_get_prompt(char *prompt, unsigned char status, char execute)
{
	char	*new;

	prompt = ft_expand_prompt(prompt);
	if (!prompt)
		return (NULL);
	if (!execute)
		ft_asprintf(&new, "\e[30;1m▶︎\e[0m %s", prompt);
	else if (status)
		ft_asprintf(&new, "\e[1;31m▶︎\e[0m %s", prompt);
	else
		ft_asprintf(&new, "\e[1;32m▶︎\e[0m %s", prompt);
	if (!new)
		return (prompt);
	free(prompt);
	return (new);
}

int	ft_run_shell(unsigned char status)
{
	char	execute;
	char	*prompt;
	char	*line;

	execute = 0;
	ft_welcome_shell();
	while (true)
	{
		prompt = ft_get_prompt(getenv("PS1"), status, execute);
		signal(SIGINT, ft_readline_handler);
		line = readline(prompt);
		signal(SIGINT, ft_sig_handler);
		if (!line && rl_eof_found)
			return (ft_printf("\e[A\e[K%sexit\n", prompt), free(prompt), 0);
		else if (!line)
			ft_perror(ERR_ERRNO, "readline");
		free(prompt);
		if (line[0])
			add_history(line);
		execute = !ft_only_space(line);
		if (execute)
			status = ft_execute(status, ft_parse(status, ft_lex(line)));
		else
			free(line);
	}
}
