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
	COMMENT,
	STRING
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
}						t_lexer;


// ABOUT tree
typedef struct s_tree
{
	t_token				*node;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;




#endif