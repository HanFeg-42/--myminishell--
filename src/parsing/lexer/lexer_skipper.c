/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skipper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/01 15:51:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*lexer_skip_comment(t_lexer *lexer)
{
	while (lexer->c)
		lexer_advance(lexer);
	return (NULL);
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (ft_issapce(lexer->c))
		lexer_advance(lexer);
}

int is_metacharacter(int c)
{
	if (c == '\0' || ft_issapce(c)
		|| c == '&' || c == '|'
		|| c == '>' || c == '<'
		|| c == '(' || c == ')'
		|| c == '#')
		return (1);
	return (0);
}

int	is_special(t_lexer *lexer, int i)
{
	if (lexer->line[lexer->i + i] == '&'
		&& lexer->line[lexer->i + i + 1] != '&')
		return (0);
	return (is_metacharacter(lexer->line[lexer->i + i]));
}

int	is_operator(t_lexer *lexer)
{
	int	c;
	int	c_next;

	c = lexer->c;
	c_next = lexer->line[lexer->i + 1];
	if (c == '|' || (c == '&' && c_next == '&')
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
