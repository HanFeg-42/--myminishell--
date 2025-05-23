/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:02 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 11:44:12 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*lexer_get_word(t_lexer *lexer)
{
	char	*word;
	int		word_size;
	int		i;

	word_size = get_word_size(lexer);
	word = ft_malloc((word_size + 1 ) * sizeof(char) );
	if (!word)
		return (NULL); // al marjo t freeyi w t exit in a clean
	i = 0;
	while (i < word_size)
	{
		word[i] = lexer->c;
		i++;
		if (i < word_size)
			lexer_advance(lexer);
	}
	word[i] = '\0';
	return (init_token(word, WORD));
}

int	get_word_size(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (!is_special(lexer->line[lexer->i + i]))
	{
		if (lexer->line[lexer->i + i] == '"')
			advance_to_next_quote(lexer, &i, '"');
		else if (lexer->line[lexer->i + i] == '\'')
			advance_to_next_quote(lexer, &i, 39);
		if (lexer->line[lexer->i + i] == '\0')
			break;
		i++;
	}
	if (*get_parser_check() == false)
		return (0);
	return (i);
}

void	advance_to_next_quote(t_lexer *lexer, int *i, int quote)
{
	if (*get_parser_check() ==  false)
		return ;
	(*i)++;
	if (lexer->line[lexer->i + (*i)] == '\0')
	{
		throw_error("Unclosed quotes!");
		return ;
	}
	while (lexer->line[lexer->i + (*i)] && lexer->line[lexer->i + (*i)] != quote)
	{
		if (lexer->i + (*i) == lexer->line_size - 1)
			throw_error("unclosed quotes!");
		(*i)++;
	}
}
