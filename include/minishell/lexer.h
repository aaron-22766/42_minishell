#ifndef LEXER_H
# define LEXER_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdio.h>
# include "../../libft/libft.h"
# include "global.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_token_identifier
{
	WORD = 0b00000001,
	COMMAND = 0b00000101,
	FILE_NAME = 0b00001001,
	HEREDOC_EOF = 0b00010001,
	OPERATOR = 0b00000010,
	I_RED = 0b00000110,
	O_RED = 0b00001010,
	HEREDOC = 0b00010010,
	O_RED_A = 0b00100010,
	PIPE = 0b01000010
};

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_tokens
{
	char			id;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// lex.c
t_tokens	*ft_lex(char *line);

// split.c
char		ft_split_at_operators(t_tokens *token);

// evaluate.c
void		ft_evaluate_tokens(t_tokens *tokens);

// check.c
char		*ft_check_syntax(t_tokens *tokens);

// utils.c
t_tokens	*ft_new_token(char *content);
void		ft_free_tokens(t_tokens *tokens);
size_t		ft_unquoted_char(char *str, const char *chars, const char *quotes);
t_tokens	*print_tokens(t_tokens *tokens);

#endif
