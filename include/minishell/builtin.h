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

// corresponding file
int		ft_cd(t_cmds *cmd);
int		ft_echo(t_cmds *cmd);
int		ft_env(t_cmds *cmd);
int		ft_exit(t_cmds *cmd);
int		ft_export(t_cmds *cmd);
int		ft_pwd(t_cmds *cmd);
int		ft_unset(t_cmds *cmd);

#endif