#ifndef BUILTIN_H
# define BUILTIN_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "minishell.h"
# include "parser.h"

// builtin.c
void	ft_check_builtin(t_cmds *cmd);
int		ft_run_builtin(t_cmds *cmd);

// cd.c
int		ft_cd(t_cmds *cmd);

// echo.c
int		ft_echo(t_cmds *cmd);

// env.c
int		ft_env(t_cmds *cmd);

// exit.c
int		ft_exit(int status, t_cmds *cmd);

// pwd.c
int		ft_pwd(t_cmds *cmd);

// unset.c
int		ft_unset(t_cmds *cmd);

// export.c
int		ft_export(t_cmds *cmd);
void	ft_print_export(void);

// utils.c
char	ft_valid_identifier(char *arg, char delim);

#endif
