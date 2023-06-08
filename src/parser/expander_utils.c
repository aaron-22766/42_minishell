#include "../../include/minishell/parser.h"

void	ft_insert_val(char **content, char *val, size_t start, size_t len)
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

ssize_t	ft_setchar(char *str, char c, ssize_t index)
{
	if (c == '/' && index < 0)
		return (ft_strlen(str));
	if (!str || index < 0 || index > (ssize_t)ft_strlen(str))
		return (-1);
	str[index] = c;
	return (index);
}

t_tokens	*ft_remove_token(t_tokens **head, t_tokens *remove)
{
	t_tokens	*current;
	t_tokens	*prev;

	current = *head;
	if (current == remove)
	{
		*head = current->next;
		free(current->content);
		free(current);
		return (*head);
	}
	while (current && current != remove)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (NULL);
	prev->next = current->next;
	free(current->content);
	free(current);
	return (prev->next);
}
