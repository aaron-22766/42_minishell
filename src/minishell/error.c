#include "../../include/minishell/minishell.h"

static int	ft_print_error(int err, char *context)
{
	if (err == ERR_ERRNO)
		return (perror(context), errno);
	if (err == ERR_MEM)
		return (ft_eprintf("memory allocation failed while %s", context), err);
	if (err == ERR_TOKEN_SYNTAX)
		return (ft_eprintf("syntax error near unexpected token `%s'", context)
			, err);
	if (err == ERR_AMBIG_RED)
		return (ft_eprintf("%s: ambiguous redirect", context), 1);
	if (err == ERR_IS_DIR)
		return (ft_eprintf("%s: is a directory", context), err);
	if (err == ERR_CMD_NOT_FOUND)
		return (ft_eprintf("%s: command not found", context), err);
	if (err == ERR_NO_FILE)
		return (ft_eprintf("%s: No such file or directory", context), 127);
	if (err == ERR_NOT_SET)
		return (ft_eprintf("%s not set", context), 1);
	return (0);
}

int	ft_perror_exe(char *exe, int err, char *context)
{
	int	ret;

	ft_eprintf("%s: ", exe);
	ret = ft_print_error(err, context);
	if (err != ERR_ERRNO)
		ft_eprintf("\n");
	return (ret);
}

int	ft_perror_builtin(char *builtin, int err, char *context)
{
	ft_eprintf("minishell: ");
	return (ft_perror_exe(builtin, err, context));
}

int	ft_perror(int err, char *context)
{
	return (ft_perror_exe("minishell", err, context));
}
