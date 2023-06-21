#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// minishell.c

// init_shell.c
void	ft_init_shell(char *ms_path);

// run_shell.c
int		ft_run_shell(int status, char execute);

// prompt.c
char	*ft_expand_prompt(char *prompt);

// env_funcs.c
int		ft_setenv(const char *name, const char *value, int overwrite);
int		ft_putenv(char *string);
int		ft_unsetenv(const char *name);

// env_utils.c
size_t	ft_environ_size(void);
char	ft_is_env_var(const char *var1, const char *var2, size_t name_len);
int		ft_existing_env_var(const char *var, ssize_t name_len);
void	ft_print_environ(void);
void	ft_free_environ(void);

// free.c
void	ft_free_commands(t_cmds *commands);

#endif
