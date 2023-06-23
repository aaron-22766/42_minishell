#include "../../include/minishell/parser.h"

static void	ft_expand_tilde(char **str, size_t t)
{
	struct stat	stats;
	ssize_t		end;
	char		*path;

	if ((*str)[t] != '~')
		return ;
	if (getenv("HOME") && ((*str)[t + 1] == '\0' || (*str)[t + 1] == '/'))
		ft_str_insert(str, getenv("HOME"), t, 1);
	else if (getenv("PWD") && (*str)[t + 1] == '+'
		&& ((*str)[t + 2] == '\0' || (*str)[t + 2] == '/'))
		ft_str_insert(str, getenv("PWD"), t, 2);
	else if (getenv("OLDPWD") && (*str)[t + 1] == '-'
		&& ((*str)[t + 2] == '\0' || (*str)[t + 2] == '/'))
		ft_str_insert(str, getenv("OLDPWD"), t, 2);
	else if ((*str)[t + 1])
	{
		end = ft_setchar(*str + t, '\0', ft_strchr_index(*str + t, '/'));
		ft_asprintf(&path, "/Users/%s", *str + t + 1);
		end = ft_setchar(*str + t, '/', end);
		if (path && !stat(path, &stats) && S_ISDIR(stats.st_mode))
			ft_str_insert(str, path, t, end);
		free(path);
	}
}

static void	ft_expand_assignment_tilde(char **str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha((*str)[i]))
		while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
			i++;
	if (i && (*str)[i] == '=')
		ft_expand_tilde(str, i + 1);
}

static char	ft_expand_tokens(int status, t_tokens **tokens)
{
	t_tokens	*tok;
	char		ret;

	tok = *tokens;
	while (tok)
	{
		if (tok->id & WORD && tok->id != HEREDOC_EOF)
		{
			ft_expand_tilde(&tok->content, 0);
			ft_expand_assignment_tilde(&tok->content);
			ret = ft_expand(&tok->content, status, tok->id);
			if (ret == RETURN_FAILURE)
				return (RETURN_FAILURE);
			else if (ret == RMV)
			{
				tok = ft_remove_token(tokens, tok);
				continue ;
			}
		}
		tok = tok->next;
	}
	return (RETURN_SUCCESS);
}

static void	ft_remove_quotes(t_tokens *tokens)
{
	size_t	i;
	char	quote;

	while (tokens)
	{
		quote = 0;
		i = -1;
		while (tokens->content[++i])
		{
			if (!quote && ft_strchr("\'\"", tokens->content[i]))
				quote = tokens->content[i];
			else if (tokens->content[i] == quote)
				quote = 0;
			else
				continue ;
			ft_strcpy(&tokens->content[i], &tokens->content[i + 1]);
			i--;
		}
		tokens = tokens->next;
	}
}

t_cmds	*ft_parse(int *status, t_tokens *tokens)
{
	t_cmds	*commands;

	if (ft_expand_tokens(*status, &tokens) == RETURN_FAILURE || !tokens)
	{
		*status = EXIT_FAILURE;
		return (ft_free_tokens(tokens), NULL);
	}
	ft_evaluate_commands(tokens);
	ft_remove_quotes(tokens);
	if (verbose)
		print_tokens(tokens, "EXPANDED TOKENS");
	commands = ft_create_commands(tokens);
	if (!commands)
	{
		*status = ERR_MEM;
		return (ft_free_tokens(tokens), NULL);
	}
	return (commands);
}
