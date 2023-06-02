#include "../../include/minishell/parser.h"

static void	ft_insert_value(char **content, char *val, size_t start, size_t len)
{
	char	*front;
	char	*back;
	char	*new;

	if (!val)
		val = "";
	front = ft_substr(*content, 0, start);
	back = ft_substr(*content, start + len, ft_strlen(*content + start + len));
	if (front && back && ft_asprintf(&new, "%s%s%s", front, val, back) != -1)
	{
		free(*content);
		*content = new;
	}
	free(front);
	free(back);
}

static char	ft_replace_var(char id, char **content, size_t start, size_t len)
{
	char	*val;
	char	temp;

	temp = content[start + len];
	content[start + len] = '\0';
	val = getenv(&content[start + 1]);
	if (start == 0 && len == ft_strlen(*content) && !val)
	{
		if (id == FILE_NAME)
			return (ft_perror(ERR_AMBIG_RED, content), RETURN_FAILURE);
		return (RMV);
	}
	content[start + len] = temp;
	if (content[start + 1] == '?')
	{
		val = ft_itoa(-42);
		if (val)
			ft_insert_value(content, val, start, len);
		free(val);
	}
	else
		ft_insert_value(content, val, start, len);
	return (RETURN_SUCCESS);
}

char	ft_expand_env_vars(char **content, char id)
{
	char	*val;
	size_t	start;
	size_t	len;
	char	ret;

	start = ft_unquoted_char(*content, "$", "\'");
	while ((*content)[start])
	{
		len = 1;
		if ((*content)[start + len] == '?')
			ret = ft_replace_var(id, *content, start, len + 1);
		else if (ft_isalpha((*content)[start + len]))
		{
			while (ft_isalnum((*content)[start + len]))
				len++;
			ret = ft_replace_var(id, *content, start, len);
		}
		if (ret != RETURN_SUCCESS)
			return (ret);
		start += ft_unquoted_char(*content + start + len, "$", "\'");
	}
	return (RETURN_SUCCESS);
}
