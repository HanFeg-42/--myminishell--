/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:03 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 19:37:53 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

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
}						t_ast_type;

// TODO : add a delimiter variable to the s_file struct

typedef struct s_file
{
	char				*filename;
	char				*delimiter;
	t_token_type		type;
	struct s_file		*next;
}						t_file;

typedef struct s_ast
{
	t_ast_type			type;
	int					i;
	char				**args;
	struct s_ast		*first_child;
	struct s_ast		*next_sibling;
	t_file				*redirect;
}						t_ast;

t_ast			*parser(t_token **token);
t_ast			*ast_compound(t_token **tokens);
t_ast			*ast_create(t_ast_type type);
void			ast_add(t_ast *head, t_ast *child);
void			token_advance(t_token **token);
int				check_and_or_token(t_token *token);
void			redirect_list(t_token **token, t_ast *subshell);
void			io_redirect(t_token **token, t_ast *simple_cmd);
t_file			*redirect_create(int type, char *filename, char *delim);
void			redirect_add(t_file **redirect, t_file *new);
int				is_token_redirect(t_token *token);
void			add_args(t_token **token, t_ast *simple_cmd);
void			*syntax_error(char *err);
int				is_empty_cmd(t_ast *simple_cmd);
void			heredoc_handler(char *eof, t_file **redirect);
void			expand(t_ast *ast);
void			expand_file(t_file *red);
void			arg_size(t_token *token);

#endif