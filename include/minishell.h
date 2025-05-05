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
// #include "hanane.h"


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

// About token
typedef enum e_token_type
{
	ID,			//0
	WORD,		//1
	AND,		//2
	OR,			//3
	PIPE,		//4
	INPUT_RED,	//5
	OUTPUT_RED,	//6
	APPEND,		//7
	HERE_DOC,	//8
	OPAREN,		//9
	CPAREN,		//10
	EOI			//11
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
t_token			*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token			*lexer_advance_with2(t_lexer *lexer, t_token *token);
t_token			*lexer_advance_with3(t_lexer *lexer, t_token *token);
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


// ==================-------expander--------=============================

// ------------------------getters------------------
int *get_parser_check(void);

// checkers
int				is_special(int c);
int				is_operator(int c);
int				is_redirection(int c);

// unwanted function
void 			throw_error(char *err);
void 			finish(char *line);
int				get_word_size(t_lexer *lexer);
void			advance_to_next_quote(t_lexer *lexer, int *i, int quote);


// " => 34
// ' => 39


#include "./ast.h"
// //========================================
// typedef enum e_ast_type
// {
	// 	AST_CMD_LIST,
	// 	AST_COMPOUND,
	// 	AST_PIPELINE,
	// 	AST_COMMANDD,
	// 	AST_SUBSHELL,
	// 	AST_SIMPLE_CMD,
// 	AST_AND,
// 	AST_OR
// 	// AST_REDIRECT_LIST,
// 	// AST_IO_REDIRECT,
// }               ast_type;

// typedef struct s_file
// {
// 	t_token_type type;
// 	char *filename;
// 	struct s_file *next;
// }               t_file;

// typedef struct s_ast
// {
// 	ast_type    type;
// 	struct ast  *first_child;
// 	struct ast  *next_sibling;
// 	char        **args;
// 	int         i;
// 	t_file      *redirect;
// }               t_ast;

// t_ast           *ast_create(ast_type type);
// void            ast_add(t_ast *head, t_ast *child);
// t_ast           *ast_last(t_ast *ast);
// void            token_advance(t_token **token);
// int check_and_or_token(t_token *token);

// t_ast			*ast_compound(t_token **tokens);
// t_ast			*ast_pipeline(t_token **tokens);
// t_ast			*ast_command(t_token **tokens);
// t_ast			*ast_simple_command(t_token **tokens);
// void			io_redirect(t_token **token, t_ast *simple_cmd);
// t_file			*redirect_create(int type, char *filename);
// int				is_token_redirect(t_token *token);
// void			add_args(t_token **token, t_ast *simple_cmd);
// t_ast			*ast_subshell(t_token **token);
// void redirect_list(t_token **token ,t_ast *subshell);
// void redirect_list(t_token **token ,t_ast *subshell);
// void *syntax_error(char *err);
// void heredoc(char *delim);

// t_ast *parser(t_token **token);
// void ast_print(t_ast *ast);
// void print_args(char **args);
// void print_redirect(t_file *redirect);
#endif