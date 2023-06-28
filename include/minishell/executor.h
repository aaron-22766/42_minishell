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

// pipeline.c
int		ft_pipeline(t_cmds *cmd, int pipe_in);
void	ft_close_fds(int pipe_in, int fd[2], char condition);

// child.c
void	ft_child(t_cmds *cmd, int fd[2], int pipe_in);

// redirections.c
void	ft_create_redirections(int status, t_cmds *cmd);

#endif
