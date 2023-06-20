#include "../../include/minishell/minishell.h"

static char	ft_only_space(char *line)
{
	size_t	i;

	if (!line)
		return (false);
	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (false);
	return (true);
}

static char	*ft_get_prompt(char *prompt, int status, char execute)
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

int	ft_run_shell(int status)
{
	char	execute;
	char	*prompt;
	char	*line;

	execute = 0;
	while (true)
	{
		g_ctrlc = false;
		prompt = ft_get_prompt(getenv("PS1"), status, execute);
		signal(SIGINT, ft_readline_handler);
		line = readline(prompt);
		signal(SIGINT, ft_sig_handler);
		if (!line && rl_eof_found)
			return (ft_printf("\e[A\e[K%sexit\n", prompt), free(prompt), 0);
		free(prompt);
		if (!line)
			status = ft_perror(ERR_ERRNO, "readline");
		if (line && line[0])
			add_history(line);
		execute = !ft_only_space(line);
		if (execute)
			status = ft_execute(status, ft_parse(status, ft_lex(line)));
		else
			free(line);
	}
}
