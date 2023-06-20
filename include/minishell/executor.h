#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "parser.h"
# include "builtin.h"

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// execute.c
int		ft_execute(int status, t_cmds *commands);

// child.c
int		ft_create_child(int status, t_cmds *cmd);

// redirections.c
char	ft_install_redirections(int status, t_cmds *command);

#endif