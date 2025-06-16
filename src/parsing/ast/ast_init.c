/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:48:12 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 17:52:02 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast	*ast_create(t_ast_type type)
{
	t_ast	*new;

	new = gc_alloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->type = type;
	new->first_child = NULL;
	new->next_sibling = NULL;
	new->args = NULL;
	new->i = 0;
	new->redirect = NULL;
	return (new);
}

static t_ast	*ast_last(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast)
	{
		if (ast->next_sibling == NULL)
			break ;
		ast = ast->next_sibling;
	}
	return (ast);
}

void	ast_add(t_ast *head, t_ast *child)
{
	t_ast	*last;

	if (!head || !child)
		return ;
	if (head->first_child == NULL)
	{
		head->first_child = child;
		return ;
	}
	last = ast_last(head->first_child);
	last->next_sibling = child;
}

void	token_advance(t_token **token)
{
	if (!token || !(*token))
		return ;
	*token = (*token)->next;
}

// void	add_args(t_token **token, t_ast *simple_cmd)
// {
// 	simple_cmd->args = ft_realloc(simple_cmd->args,
// 			sizeof(char *) * (simple_cmd->i + 2));
// 	if (!simple_cmd->args)
// 		return ;
// 	simple_cmd->args[simple_cmd->i++] = ft_strdup((*token)->value);
// 	simple_cmd->args[simple_cmd->i] = NULL;
// 	token_advance(token);
// }

void	add_args(t_token **token, t_ast *simple_cmd)
{
	if (!simple_cmd->args)
		simple_cmd->args = gc_alloc(sizeof(char *) * (*get_arg_size() + 2));
	simple_cmd->args[simple_cmd->i++] = ft_strdup((*token)->value);
	simple_cmd->args[simple_cmd->i] = NULL;
	token_advance(token);
}
