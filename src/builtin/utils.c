#include "../../include/minishell/builtin.h"

char	ft_valid_identifier(char *arg, char delim)
{
	size_t	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[i] && arg[i] != delim)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
