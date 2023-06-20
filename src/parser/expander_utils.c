#include "../../include/minishell/parser.h"

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
