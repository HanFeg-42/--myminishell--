#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../garbage_collector/gc.h"


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

// About token
typedef enum e_token_type
{
	ID,			//0
	WORD,		//1
	STAR,		//2
	FILE_,		//3
	AND,		//4
	OR,			//5
	PIPE,		//6
	INPUT_RED,	//7
	OUTPUT_RED,	//8
	APPEND,		//9
	HERE_DOC,	//10
	DQUOTE,		//11
	SQUOTE,		//12
	EQUALS,		//13
	OPAREN,		//14
	CPAREN,		//15
	EXPANSION,	//16
	SUBSHELL,	//17
	COMMENT,	//18
	TOKEN_EOI	//19
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

// ==================--------lexer-------=============================
t_lexer			*init_lexer(char *line);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespaces(t_lexer *lexer);
t_token			*lexer_get_word(t_lexer *lexer);
t_token			*lexer_advance_current(t_lexer *lexer, int type);
t_token			*lexer_advance_with2(t_lexer *lexer, t_token *token);
t_token			*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token			*lexer_skip_comment(t_lexer *lexer);
t_token			*lexer_next_token(t_lexer *lexer);
t_token			*lexer_operator(t_lexer *lexer);
t_token			*lexer_redirection(t_lexer *lexer);

// ==================--------token-------=============================
t_token			*tokenizer(char *line);
t_token			*init_token(char *value, int type);
void			token_addback(t_token **tok_head, t_token *token);
t_token			*token_last(t_token *tok_head);
void			token_print(t_token *tok);
void			token_free_list(t_token *tok);

// ==================--------parser-------=============================
void	parser(t_token *tok);
void	parse_quotes(t_token *tok);
void	parse_parentheses(t_token *tok);

// ==================-------expander--------=============================

// ------------------------getters------------------
int *get_parser_check(void);

// checkers
int				is_special(int c);
int				is_operator(int c);
int				is_redirection(int c);

// unwanted function
int				get_q_size(t_lexer *lexer, int quote);
void			clean_exit(t_lexer *lexer, t_token *token);
void 			throw_error(char *err);
void 			finish(char *line);
int				get_word_size(t_lexer *lexer);
void			advance_to_next_quote(t_lexer *lexer, int *i, int quote);


// " => 34
// ' => 39

#endif