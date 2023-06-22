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

static char	*ft_get_prompt(int status, char execute)
{
	char	*prompt;
	char	*new;
	char	malloced;

	malloced = true;
	prompt = ft_expand_prompt(getenv("PS1"));
	if (!prompt)
	{
		malloced = false;
		prompt = "";
	}
	if (!execute)
		ft_asprintf(&new, "%s %s", GRAY_INCIDATOR, prompt);
	else if (status)
		ft_asprintf(&new, "%s %s", RED_INCIDATOR, prompt);
	else
		ft_asprintf(&new, "%s %s", GREEN_INCIDATOR, prompt);
	if (!new && malloced == true)
		return (prompt);
	if (!new)
		return (NULL);
	if (malloced == true)
		free(prompt);
	return (new);
}

int	ft_run_shell(int status, char execute)
{
	char	*prompt;
	char	*line;

	while (true)
	{
		g_ctrlc = false;
		prompt = ft_get_prompt(status, execute);
		signal(SIGINT, ft_readline_handler);
		if (isatty(fileno(stdin)))//remove
			line = readline(prompt);
		else//remove
		{//remove
			char *tester = get_next_line(fileno(stdin));//remove
			line = ft_strtrim(tester, "\n");//remove
			free(tester);//remove
		}//remove
		signal(SIGINT, ft_sig_handler);
		if (!line/* && rl_eof_found*/)
			return (/*ft_printf("%sexit\n", prompt), */free(prompt), 0);
		free(prompt);
		// if (!line)
		// 	return (ft_perror(ERR_ERRNO, "readline"));
		if (line && line[0])
			add_history(line);
		execute = !ft_only_space(line);
		if (execute)
			status = ft_execute(status, ft_parse(status, ft_lex(line)));
		else
			free(line);
	}
}
