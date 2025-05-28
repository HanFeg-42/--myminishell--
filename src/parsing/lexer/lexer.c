/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:07 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 12:11:18 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = ft_malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->line = ft_strdup(line);
	lexer->i = 0;
	lexer->c = line[0];
	lexer->line_size = ft_strlen(line);
	return (lexer);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	if (*get_parser_check() == false)
		return (NULL);
	while (lexer->c)
	{
		lexer_skip_whitespaces(lexer);
		if (is_operator(lexer->c))
			return (lexer_operator(lexer));
		if (is_redirection(lexer->c))
			return (lexer_redirection(lexer));
		if (lexer->c == '#')
			return (lexer_advance_with(lexer,
					lexer_skip_comment(lexer)));
		if (!is_special(lexer->c))
			return (lexer_advance_with(lexer, lexer_get_word(lexer)));
		if (lexer->i == lexer->line_size - 1)
			return (init_token(ft_strdup("newline"), EOI));
	}
	return (NULL);
}

t_token	*lexer_operator(t_lexer *lexer)
{
	if (lexer->c == '&')
	{
		if (lexer->line[lexer->i + 1] == '&')
			return (lexer_advance_with2(lexer,
					init_token(ft_strdup("&&"), AND)));
		syntax_error("&");
	}
	if (lexer->c == '|')
	{
		if (lexer->line[lexer->i + 1] == '|')
			return (lexer_advance_with2(lexer,
					init_token(ft_strdup("||"), OR)));
		return (lexer_advance_current(lexer, PIPE));
	}
	if (lexer->c == '(')
		return (lexer_advance_current(lexer, OPAREN));
	if (lexer->c == ')')
		return (lexer_advance_current(lexer, CPAREN));
	return (NULL);
}

t_token	*lexer_redirection(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer->line[lexer->i + 1] == '>')
			return (lexer_advance_with2(lexer,
					init_token(ft_strdup(">>"), APPEND)));
		return (lexer_advance_current(lexer, OUTPUT_RED));
	}
	if (lexer->c == '<')
	{
		if (lexer->line[lexer->i + 1] == '<')
			return (lexer_advance_with2(lexer,
					init_token(ft_strdup("<<"), HERE_DOC)));
		return (lexer_advance_current(lexer, INPUT_RED));
	}
	return (NULL);
}
