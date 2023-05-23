#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "../libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_errors
{
	RETURN_SUCCESS,
	RETURN_FAILURE,
	ERR_MEM
};

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_cmds
{
	char			*path;
	char			**argv;
	int				in_fd;
	int				out_fd;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_minishell
{
	bool		verbose;
	t_cmds		*commands;
}	t_minishell;

/* ************************************************************************** */
/*                              GLOBAL VARIABLE                               */
/* ************************************************************************** */

t_minishell	g_data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// init_shell.c
void	ft_init_shell(void);

// run_shell.c
void	ft_run_shell(void);

// free.c
void	ft_free(void);

// error.c
void	ft_perror(int err);

#endif
