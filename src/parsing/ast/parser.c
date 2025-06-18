/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:33:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/18 17:39:24 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/heredoc.h"

t_ast	*parser(t_token **token)
{
	t_ast	*ast;

	if (!(*get_parser_check()) || !(*token))
		return (NULL);
	ast = ast_compound(token);
	if (!ast)
	{
		if (!(*get_heredoc_check()))
			return (NULL);
		if ((*token))
			syntax_error((*token)->value);
		else
			syntax_error("newline");
	}
	else if (*(token))
	{
		syntax_error((*token)->prev->value);
		return (NULL);
	}
	return (ast);
}
