/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advancer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:41:59 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/11 20:32:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	lexer_advance(t_lexer *lexer)
{
	if (lexer && lexer->c)
	{
		lexer->i++;
		lexer->c = lexer->line[lexer->i];
	}
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_advance_with2(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_advance_current(t_lexer *lexer, t_token_type type)
{
	char	*token;

	token = gc_alloc(sizeof(char) + 1);
	token[0] = lexer->c;
	token[1] = '\0';
	lexer_advance(lexer);
	return (init_token(token, type));
}
