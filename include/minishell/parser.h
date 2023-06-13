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
	struct s_cmds	*next;
}	t_cmds;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// parse.c
t_cmds		*ft_parse(unsigned char status, t_tokens *tokens);

// expander.c
char		ft_expand_tokens(unsigned char status, t_tokens **tokens);
char		ft_expand_env_vars(unsigned char status, char **content,
				char *quotes, char id);

// expander_utils.c
void		ft_insert_val(char **content, char *val, size_t start, size_t len);
ssize_t		ft_setchar(char *str, char c, ssize_t index);
t_tokens	*ft_remove_token(t_tokens **head, t_tokens *remove);

// commands.c
t_cmds		*ft_create_commands(t_tokens *tokens);

// allocate_table.c
t_cmds		*ft_allocate_command_table(t_tokens *tokens);

// utils.c
void		ft_free_cmds(t_cmds *commands);
void		print_cmds(t_cmds *commands);

#endif
