/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 11:12:22 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

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

void	*syntax_error(char *err)
{
	*(get_parser_check()) = false;
	if (err)
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (NULL);
}

int	is_empty_cmd(t_ast *simple_cmd)
{
	if (!simple_cmd->args && !simple_cmd->redirect)
		return (true);
	return (false);
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
