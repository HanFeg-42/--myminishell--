/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:07 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/12 20:06:17 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*init_token(char *value, t_token_type type)
{
	t_token	*tok;

	tok = gc_alloc(sizeof(t_token));
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

t_token	*lexer_match_special_token(t_lexer *lexer, char *double_str,
	int signle_type, int double_type)
{
	if (lexer->line[lexer->i + 1] == lexer->c)
		return (lexer_advance_with2(lexer,
				init_token(ft_strdup(double_str), double_type)));
	return (lexer_advance_current(lexer, signle_type));
}

static t_token	*lexer_operator(t_lexer *lexer)
{
	if (lexer->c == '&' && lexer->line[lexer->i + 1] == '&')
		return (lexer_advance_with2(lexer,
				init_token(ft_strdup("&&"), AND)));
	if (lexer->c == '|')
		return (lexer_match_special_token(lexer, "||", PIPE, OR));
	if (lexer->c == '(')
		return (lexer_advance_current(lexer, OPAREN));
	if (lexer->c == ')')
		return (lexer_advance_current(lexer, CPAREN));
	return (NULL);
}

static t_token	*lexer_redirection(t_lexer *lexer)
{
	if (lexer->c == '>')
		return (lexer_match_special_token(lexer, ">>", OUTPUT_RED, APPEND));
	if (lexer->c == '<')
		return (lexer_match_special_token(lexer, "<<", INPUT_RED, HERE_DOC));
	return (NULL);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	if (*get_parser_check() == false)
		return (NULL);
	while (lexer->c)
	{
		lexer_skip_whitespaces(lexer);
		if (is_operator(lexer))
			return (lexer_operator(lexer));
		if (is_redirection(lexer->c))
			return (lexer_redirection(lexer));
		if (lexer->c == '#')
			return (NULL);
		if (!is_special(lexer, 0))
			return (lexer_advance_with(lexer, lexer_get_word(lexer)));
	}
	return (NULL);
}
