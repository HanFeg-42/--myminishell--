#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

// About token
typedef enum e_token_type
{
	WORD,
	// FILE,
	AND,
	OR,
	PIPE,
	INPUT_RED,
	OUTPUT_RED,
	APPEND,
	HERE_DOC,
	DQUOTE,
	SQUOTE,
	EQUALS,
	OPAREN,
	CPAREN,
	OBRACE,
	CBRACE,
	EXPANSION,
	SUBSHELL,
	COMMENT
}						t_token_type;

//token
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_lexer
{
	char				*line;
	char				c;
	int 				i;
	int					line_size;
}						t_lexer;


// ABOUT tree
typedef struct s_tree
{
	t_token				*node;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

// lexer
t_token *tokenize(char *line);
t_token *init_token(char *value, int type);

t_lexer *init_lexer(char *line);
void lexer_advance(t_lexer *lexer);
void lexer_skip_whitespaces(t_lexer *lexer);
t_token *lexer_get_word(t_lexer *lexer);
t_token *lexer_get_heredoc(t_lexer *lexer);
int get_q_size(t_lexer *lexer);
t_token *lexer_advance_current(t_lexer *lexer, int type);
t_token *lexer_advance_with2(t_lexer *lexer, t_token *token);
t_token *lexer_advance_with(t_lexer *lexer, t_token *token);
t_token *lexer_get_squote(t_lexer *lexer);
t_token *lexer_get_expansion(t_lexer *lexer);
t_token *lexer_get_dquote(t_lexer *lexer);
void clean_exit(t_lexer *lexer, t_token *token);
t_token *lexer_skip_comment(t_lexer *lexer);
t_token *lexer_next_token(t_lexer *lexer);



#endif