/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 01:25:47 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"

void	add_args(t_token **token, t_ast *simple_cmd)
{
	simple_cmd->args = ft_realloc(simple_cmd->args,
			sizeof(char *) * (simple_cmd->i + 2));
	if (!simple_cmd->args)
		return ;
	simple_cmd->args[simple_cmd->i++] = ft_strdup((*token)->value);
	simple_cmd->args[simple_cmd->i] = NULL;
	token_advance(token);
}

int	is_empty_cmd(t_ast *simple_cmd)
{
	return (!simple_cmd->args && !simple_cmd->redirect);
}

int	check_and_or_token(t_token *token)
{
	if (!token)
		return (-1);
	if (token->type == AND)
		return (AST_AND);
	else if (token->type == OR)
		return (AST_OR);
	return (-1);
}
