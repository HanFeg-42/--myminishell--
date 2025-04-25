#ifndef AST_H
#define AST_H

#include "minishell.h"

typedef enum e_ast_type
{
	AST_CMD_LIST,
	AST_COMPOUND,
	AST_PIPELINE,
	AST_COMMANDD,
	AST_SUBSHELL,
	AST_SIMPLE_CMD,
	AST_REDIRECT_LIST,
	AST_IO_REDIRECT,
	AST_AND,
	AST_OR
}               ast_type;

typedef struct s_ast
{
	ast_type    type;
	struct ast  *first_child;
	struct ast  *next_sibling;
	char        **args;
	int         i;
	t_file      *redirect;
}               t_ast;

typedef struct s_file
{
	t_token_type type;
	char *filename;
	struct s_file *next;

}               t_file;

t_ast           *ast_create(ast_type type);
void            ast_add(t_ast *head, t_ast *child);
t_ast           *ast_last(t_ast *ast);
void            token_advance(t_token **token);
t_ast			*ast_compound(t_token *tokens);
t_ast			*ast_pipeline(t_token *tokens);
t_ast			*ast_command(t_token *tokens);
t_ast			*ast_simple_command(t_token *tokens);
void			io_redirect(t_token **token, t_ast *simple_cmd);
t_file			*redirect_create(int type, char *filename);
int				is_token_redirect(t_token *token);
void			add_args(t_token **token, t_ast *simple_cmd);
t_ast			*ast_subshell(t_token *token);

#endif