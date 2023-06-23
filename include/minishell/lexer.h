#ifndef LEXER_H
# define LEXER_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "global.h"

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_token_id
{
	WORD = 0b00000001,
	IN_FILE = 0b00000101,
	OUT_FILE = 0b00001001,
	HEREDOC_EOF = 0b00010001,
	OUT_A_FILE = 0b00100001,
	COMMAND = 0b01000001,
	OPERATOR = 0b00000010,
	IN_RED = 0b00000110,
	OUT_RED = 0b00001010,
	HEREDOC = 0b00010010,
	OUT_A_RED = 0b00100010,
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
t_tokens	*ft_lex(int *status, char *line);

// split.c
char		ft_split_at_operators(t_tokens *token);

// evaluate.c
int			ft_evaluate_tokens(t_tokens *tokens);
void		ft_evaluate_commands(t_tokens *tokens);

// utils.c
t_tokens	*ft_new_token(char *content);
void		ft_free_tokens(t_tokens *tokens);
size_t		ft_unquoted_char(char *str, const char *chars, const char *quotes);
t_tokens	*print_tokens(t_tokens *tokens, const char *title);

#endif
