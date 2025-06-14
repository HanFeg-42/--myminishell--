/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skipper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/12 22:55:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

int	is_metacharacter(int c)
{
	return (c == ' ' || c == '\t'
		|| c == '&' || c == '|'
		|| c == '>' || c == '<'
		|| c == '(' || c == ')'
		|| c == '#' || c == '\0');
}

int	is_special(t_lexer *lexer, int i)
{
	if (lexer->line[lexer->i + i] == '&'
		&& lexer->line[lexer->i + i + 1] != '&')
		return (false);
	return (is_metacharacter(lexer->line[lexer->i + i]));
}

int	is_operator(t_lexer *lexer)
{
	int	c;
	int	c_next;

	c = lexer->c;
	if (!c)
		return (false);
	c_next = lexer->line[lexer->i + 1];
	return (c == '|' || (c == '&' && c_next == '&')
		|| c == '(' || c == ')');
}

int	is_redirection(int c)
{
	return (c == '<' || c == '>');
}
