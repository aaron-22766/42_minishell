#ifndef GLOBAL_H
# define GLOBAL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libft/libft.h"

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_return
{
	RETURN_SUCCESS,
	RETURN_FAILURE
};

enum e_errors
{
	ERR_ERRNO,
	ERR_NOT_SET = -1,
	ERR_MEM = 12,
	ERR_TOKEN_SYNTAX = 258,
	ERR_AMBIG_RED = -2,
	ERR_IS_DIR = 126,
	ERR_CMD_NOT_FOUND = 127,
	ERR_NO_FILE = -3
};

enum e_builtins
{
	B_NO,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

/* ************************************************************************** */
/*                              GLOBAL VARIABLE                               */
/* ************************************************************************** */

bool	verbose;
char	g_ctrlc;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// signals.c
void	ft_readline_handler(int sig);
void	ft_sig_handler(int sig);

// error.c
int		ft_perror(int err, char *context);
int		ft_perror_builtin(char *builtin, int err, char *context);
int		ft_perror_exe(char *exe, int err, char *context);

#endif