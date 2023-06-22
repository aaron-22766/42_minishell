#include "../../include/minishell/minishell.h"

static size_t	ft_next_escape(char *prompt, size_t prev)
{
	while (prompt[prev])
	{
		if (prompt[prev] == '\\')
			return (prev);
		prev++;
	}
	return (prev);
}

static char	*ft_working_directory(char esc)
{
	char	*pwd;
	char	*home;
	char	*val;
	char	cwd;

	cwd = false;
	pwd = getenv("PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		cwd = true;
	}
	if (!pwd)
		return (NULL);
	val = ft_strdup(pwd);
	home = getenv("HOME");
	if (pwd && home && ft_strnstr(pwd, home, ft_strlen(pwd)) == pwd)
		ft_str_insert(&val, "~", 0, ft_strlen(home));
	if (esc == 'W')
		ft_str_insert(&val, "", 0, ft_strrchr_index(val, '/')
			+ !!ft_strcmp(pwd, "/"));
	if (cwd)
		free(pwd);
	return (val);
}

static char	*ft_complex_value(char esc)
{
	char	*user;
	char	*hostname;

	if (esc == 'u')
	{
		user = getenv("USER");
		if (user)
			return (ft_strdup(user));
	}
	else if (ft_strchr("hH", esc))
	{
		hostname = getenv("HOSTNAME");
		if (hostname && esc == 'h')
			return (ft_substr(hostname, 0, ft_strchr_index(hostname, '.')));
		if (hostname && esc == 'H')
			return (ft_strdup(hostname));
	}
	return (NULL);
}

static char	*ft_escape_value(char esc)
{
	if (esc == '[')
		return (ft_substr("\001", 0, 1));
	if (esc == ']')
		return (ft_substr("\002", 0, 1));
	if (esc == 'a')
		return (ft_substr("\a", 0, 1));
	if (esc == 'e')
		return (ft_substr("\e", 0, 1));
	if (esc == 'n')
		return (ft_substr("\n", 0, 1));
	if (esc == 'r')
		return (ft_substr("\r", 0, 1));
	if (esc == '\\')
		return (ft_substr("\\", 0, 1));
	if (esc == 's')
		return (ft_strdup("minishell"));
	if (ft_strchr("wW", esc))
		return (ft_working_directory(esc));
	return (ft_complex_value(esc));
}

char	*ft_expand_prompt(char *prompt)
{
	size_t	backslash;
	char	*val;

	if (!prompt)
		prompt = ft_strdup("\\h:\\W \\u\\$ ");
	else
		prompt = ft_strdup(prompt);
	if (prompt)
		backslash = ft_next_escape(prompt, 0);
	while (prompt && prompt[backslash])
	{
		val = ft_escape_value(prompt[backslash + 1]);
		if (val)
		{
			ft_str_insert(&prompt, val, backslash, 2);
			backslash += ft_strlen(val);
			free(val);
		}
		else
			ft_str_insert(&prompt, "", backslash, 1);
		if (prompt)
			backslash = ft_next_escape(prompt, backslash);
	}
	return (prompt);
}
