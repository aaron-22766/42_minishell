#ifndef GLOBAL_H
# define GLOBAL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

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