#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/libft.h"

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
	EXPANSION,	//18
	SUBSHELL,	//19
	COMMENT		//20
}						t_token_type;

typedef enum e_cmd_type
{
	COMMAND,
	ARG
}						t_cmd_type;

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

typedef struct s_file
{
	t_token_type		file_type;
	char				*name;
	struct s_file		*next;
}						t_file;


// ABOUT tree
typedef struct s_tree
{
	t_token				*node;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

typedef struct s_AST
{
	t_token_type		node_type;
	char				*value;
	char				**arg;
	t_file				*file;
	struct s_tree		*left;
	struct s_tree		*right;
}				t_AST;

// garbage collector
typedef struct s_gc
{
	void				*addr;
	struct s_gc			*next;
	struct s_gc			*prev;
}						t_gc;


// ==================--------lexer-------=============================
t_lexer			*init_lexer(char *line);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespaces(t_lexer *lexer);
t_token			*lexer_get_word(t_lexer *lexer);
t_token			*lexer_get_heredoc(t_lexer *lexer);
t_token			*lexer_advance_current(t_lexer *lexer, int type);
t_token			*lexer_advance_with2(t_lexer *lexer, t_token *token);
t_token			*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token			*lexer_get_squote(t_lexer *lexer);
t_token			*lexer_get_expansion(t_lexer *lexer);
t_token			*lexer_get_dquote(t_lexer *lexer);
t_token			*lexer_skip_comment(t_lexer *lexer);
t_token			*lexer_next_token(t_lexer *lexer);
t_token			*lexer_operator(t_lexer *lexer);
t_token			*lexer_redirection(t_lexer *lexer);
t_token			*lexer_quote_or_paren(t_lexer *lexer);

// ==================--------token-------=============================
t_token			*tokenizer(char *line);
t_token			*init_token(char *value, int type);
void			token_addback(t_token **tok_head, t_token *token);
t_token			*token_last(t_token *tok_head);
void			token_print(t_token *tok);
void			token_free_list(t_token *tok);

// ==================--------parser-------=============================
void	parser(t_token *tok);

// ==================-------expander--------=============================

// ==================---------gc---------=============================
void			*ft_malloc(size_t size);
t_gc			**get_gc_head(void);
t_gc			*gc_new(void *content);
void			gc_addback(t_gc **head, t_gc *new);
t_gc			*gc_last(t_gc *head);
void			gc_print(t_gc *head);
void			free_one(void *addr);
void			free_all(void);
void			free_mid_node(t_gc *node);
void			free_first_node(t_gc *node);
void			free_last_node(t_gc *node);
void			free_lonley_node(t_gc *node);

// checkers
int				is_special(int c);
int				is_operator(int c);
int				is_redirection(int c);

// unwanted function
int				get_dq_size(t_lexer *lexer);
void			clean_exit(t_lexer *lexer, t_token *token);
void 			throw_error(char *err);
void 			finish(char *line);

// " => 34
// ' => 39

#endif