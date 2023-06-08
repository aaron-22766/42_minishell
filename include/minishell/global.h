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
	ERR_MEM,
	ERR_TOKEN_SYNTAX,
	ERR_AMBIG_RED
};

/* ************************************************************************** */
/*                              GLOBAL VARIABLE                               */
/* ************************************************************************** */

bool	verbose;
// pid_t	g_child_pid;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// error.c
void	ft_perror(int err, char *context);
void	ft_perror_builtin(char *builtin, int err, char *context);
void	ft_perror_exe(char *exe, int err, char *context);

#endif