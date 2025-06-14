/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:58 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 15:46:28 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	copy_characters_until_quote(t_expand *exp, char *file)
{
	char	*curr_pos;
	char	*sq_pos;

	exp->stat = SINGLE_QUOTED;
	curr_pos = file + exp->pos;
	sq_pos = ft_strchr(curr_pos + 1, '\'');
	exp->word = ft_strjoin(exp->word,
			ft_substr(curr_pos, 0, sq_pos - curr_pos));
	exp->pos += sq_pos - curr_pos;
}

static void	expand_token(t_expand *exp, char **file, char **quote_pos)
{
	char	*curr;
	char	*quote;
	char	*dollar_pos;

	curr = *file + exp->pos;
	quote = *quote_pos;
	while (*curr && curr < quote)
	{
		dollar_pos = ft_strnchr(curr, '$', quote - curr);
		if (!dollar_pos)
		{
			exp->word = ft_strjoin(exp->word,
					ft_substr(curr, 0, quote - curr));
			break ;
		}
		exp->word = ft_strjoin(exp->word,
				ft_substr(curr, 0, dollar_pos - curr));
		exp->word = ft_strjoin(exp->word, get_env_name(dollar_pos));
		curr = skip_env_var(dollar_pos + 1);
	}
	exp->pos += quote - *file - exp->pos;
}

void	expand_inside_double_quote(t_expand *exp, char *file)
{
	char	*dq_pos;

	exp->stat = DOUBLE_QUOTED;
	dq_pos = ft_strchr(file + exp->pos + 1, '"');
	expand_token(exp, &file, &dq_pos);
}

void	expand_unquoted(t_expand *exp, char *file)
{
	char	*q_pos;

	exp->stat = NORMAL;
	q_pos = first_quote_occ(file + exp->pos + 1);
	if (!q_pos)
		q_pos = ft_strchr(file + exp->pos + 1, '\0');
	expand_token(exp, &file, &q_pos);
}

void	expand_parameter(t_expand *exp)
{
	char	*word;

	word = exp->args[exp->i];
	exp->word = ft_strdup("");
	while (exp->pos < (int)ft_strlen(word) && word[exp->pos])
	{
		if (word[exp->pos] == '\'' && exp->stat == NORMAL)
			copy_characters_until_quote(exp, word);
		else if (word[exp->pos] == '"' && exp->stat == NORMAL)
			expand_inside_double_quote(exp, word);
		else
			expand_unquoted(exp, word);
	}
}
