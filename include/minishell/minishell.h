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
# include "../../libft/libft.h"

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

/* ************************************************************************** */
/*                              GLOBAL VARIABLE                               */
/* ************************************************************************** */

bool	verbose;
// pid_t	g_child_pid;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// minishell.c

// init_shell.c
void	ft_init_shell(void);

// run_shell.c
void	ft_run_shell(void);

// env_funcs.c
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_putenv(char *string);
int		ft_unsetenv(const char *name);

// env_utils.c
size_t	ft_environ_size(void);
bool	ft_is_env_var(const char *var1, const char *var2, size_t name_len);
int		ft_existing_env_var(const char *var, size_t name_len);
void	ft_print_environ(void);
void	ft_free_environ(void);

// free.c
void	ft_free_commands(t_cmds *commands);

// error.c
void	ft_perror(int err);

#endif
