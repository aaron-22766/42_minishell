#ifndef BUILTIN_H
# define BUILTIN_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "minishell.h"
# include "parser.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// builtins
int		ft_check_builtin_parent(t_cmds *command);
int		ft_check_builtin_child(t_cmds *command);
int		ft_cd(t_cmds *command);
void	ft_echo(t_cmds *command);
void	ft_env(t_cmds *command);
void	ft_exit(t_cmds *command);
void	ft_export(t_cmds *command);
int		ft_pwd(t_cmds *command);
void	ft_unset(t_cmds *command);

#endif