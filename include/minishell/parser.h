#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"
# include "lexer.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define RMV -1

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_cmds
{
	char			*path;
	char			**argv;
	t_tokens		*io_red;
	int				fd_in;
	int				fd_out;
	char			builtin;
	struct s_cmds	*next;
}	t_cmds;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// parse.c
t_cmds		*ft_parse(int *status, t_tokens *tokens);

// expander.c
char		ft_expand_tokens(int status, t_tokens **tokens);

// expand.c
char		ft_expand(char **str, int status, char id);

// commands.c
t_cmds		*ft_create_commands(t_tokens *tokens);

// allocate_table.c
t_cmds		*ft_allocate_command_table(t_tokens *tokens);

// utils.c
t_cmds		*ft_free_cmd(t_cmds *cmd);
void		ft_free_commands(t_cmds *cmd);
ssize_t		ft_setchar(char *str, char c, ssize_t index);
void		print_cmds(t_cmds *commands);

#endif
