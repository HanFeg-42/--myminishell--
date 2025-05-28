/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:28:27 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 09:32:48 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

t_ast	*ast_compound(t_token **tokens)
{
	t_ast	*ast_head;
	t_ast	*pipeline;
	int		type;

	ast_head = ast_create(AST_COMPOUND);
	if (!ast_head)
		return (NULL);
	while (1)
	{
		pipeline = ast_pipeline(tokens);
		if (!pipeline)
			return (NULL);
		ast_add(ast_head, pipeline);
		type = check_and_or_token(*tokens);
		if (type < 0)
			break ;
		ast_add(ast_head, ast_create(type));
		token_advance(tokens);
	}
	return (ast_head);
}

t_ast	*ast_pipeline(t_token **tokens)
{
	t_ast	*pipeline;
	t_ast	*command;

	pipeline = ast_create(AST_PIPELINE);
	if (!pipeline)
		return (NULL);
	while (1)
	{
		command = ast_command(tokens);
		if (!command)
			return (NULL);
		ast_add(pipeline, command);
		if (!(*tokens) || (*tokens)->type != PIPE)
			break ;
		token_advance(tokens);
	}
	return (pipeline);
}

t_ast	*ast_command(t_token **tokens)
{
	t_ast	*command;
	t_ast	*result;

	command = ast_create(AST_COMMANDD);
	if (!command)
		return (NULL);
	if ((*tokens) && (*tokens)->type == OPAREN)
	{
		token_advance(tokens);
		result = ast_subshell(tokens);
		if (!result)
			return (NULL);
	}
	else
		result = ast_simple_command(tokens);
	if (!result)
		return (NULL);
	ast_add(command, result);
	return (command);
}

t_ast	*ast_simple_command(t_token **tokens)
{
	t_ast	*simple_cmd;

	simple_cmd = ast_create(AST_SIMPLE_CMD);
	if (!simple_cmd)
		return (NULL);
	while (1)
	{
		if (is_token_redirect(*tokens))
		{
			io_redirect(tokens, simple_cmd);
			if (!(*get_parser_check()))
				return (NULL);
		}
		else if ((*tokens) && (*tokens)->type == WORD)
			add_args(tokens, simple_cmd);
		else
		{
			if (is_empty_cmd(simple_cmd))
				return (syntax_error(NULL));
			break ;
		}
	}
	return (simple_cmd);
}

t_ast	*ast_subshell(t_token **token)
{
	t_ast	*subshell;
	t_ast	*compound;

	subshell = ast_create(AST_SUBSHELL);
	if (!subshell)
		return (NULL);
	compound = ast_compound(token);
	if (!compound)
		return (NULL);
	ast_add(subshell, compound);
	if ((*token) && (*token)->type == CPAREN)
		token_advance(token);
	else
		return (syntax_error(NULL));
	if (is_token_redirect(*token))
		redirect_list(token, subshell);
	else if ((*token) && (*token)->type == WORD)
		return (syntax_error(NULL));
	if (!(*get_parser_check()))
		return (NULL);
	return (subshell);
}
