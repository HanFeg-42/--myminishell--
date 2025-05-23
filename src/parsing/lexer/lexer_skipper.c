/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skipper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:05 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 11:45:10 by hfegrach         ###   ########.fr       */
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

int	is_special(int c)
{
	if (c == '\0' || ft_issapce(c)
		|| c == '&' || c == '|'
		|| c == '>' || c == '<'
		|| c == '(' || c == ')'
		|| c == '#')
		return (1);
	return (0);
}

int	is_operator(int c)
{
	if (c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
