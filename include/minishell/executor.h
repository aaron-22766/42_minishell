#ifndef EXECUTOR_H
# define EXECUTOR_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "parser.h"

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// execute.c
unsigned char	ft_execute(unsigned char status, t_cmds *commands);

// child.c
unsigned char	ft_create_child(unsigned char status, t_cmds *cmd,
					t_cmds *commands);

// redirections.c
char			ft_install_redirections(unsigned char status, t_cmds *command);

#endif