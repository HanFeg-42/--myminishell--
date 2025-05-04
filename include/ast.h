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
	AST_AND,
	AST_OR
	// AST_REDIRECT_LIST,
	// AST_IO_REDIRECT,
}               ast_type;

typedef struct s_file
{
	t_token_type type;
	char *filename;
	struct s_file *next;
}               t_file;

typedef struct s_ast
{
	ast_type    type;
	struct s_ast  *first_child;
	struct s_ast  *next_sibling;
	char        **args;
	int         i;
	t_file      *redirect;
}               t_ast;

t_ast           *ast_create(ast_type type);
void            ast_add(t_ast *head, t_ast *child);
t_ast           *ast_last(t_ast *ast);
void            token_advance(t_token **token);
int check_and_or_token(t_token *token);

t_ast			*ast_compound(t_token **tokens);
t_ast			*ast_pipeline(t_token **tokens);
t_ast			*ast_command(t_token **tokens);
t_ast			*ast_simple_command(t_token **tokens);
void			io_redirect(t_token **token, t_ast *simple_cmd);
t_file			*redirect_create(int type, char *filename);
void redirect_add(t_file **redirect, t_file *new);
int				is_token_redirect(t_token *token);
void			add_args(t_token **token, t_ast *simple_cmd);
t_ast			*ast_subshell(t_token **token);
void redirect_list(t_token **token ,t_ast *subshell);
void redirect_list(t_token **token ,t_ast *subshell);
void *syntax_error(char *err);
void heredoc(char *delim);

t_ast *parser(t_token **token);
void ast_print(t_ast *ast);
void print_args(char **args);
void print_redirect(t_file *redirect);
int is_empty_cmd(t_ast *simple_cmd);

void *ft_realloc(void *ptr, size_t size);
void    copy_ptr(char **ptr, char **new_ptr);
void    free_old_ptr(char **ptr);

//get_next_line
char	*ft_strjoin_(char *s1, char *s2);
void	fill_in_save(int fd, ssize_t *rd, char **save, char **buff);
char	*read_line(char **save, ssize_t rd);
char	*get_next_line(int fd, int f);

#endif