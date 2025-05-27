/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 12:02:14 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

void	expand_param(t_expand *exp)
{
	char	*word;

	word = exp->args[exp->i];
	exp->word = ft_strdup("");
	while (exp->pos < (int)ft_strlen(word) && word[exp->pos])// red lbal l sigle quote & double quote
	{
		if (word[exp->pos] == 34 && exp->stat == 0)
			expand_inside_double_quote(exp, word);// inside double quotes
		else if ((word[exp->pos] == 34 && exp->stat == 1)
			|| (word[exp->pos] == 39 && exp->stat == 2))
			expand_unquoted(exp, word);// outside quotes
		else if (word[exp->pos] == 39 && exp->stat == 0)
			copy_characters_until_quote(exp, word);// inside single quotes
		else
			expand_unquoted(exp, word);// outside quotes
	}
}

void	copy_characters_until_quote(t_expand *exp, char *file)
{
	char	*curr_pos;
	char	*sq_pos;

	exp->stat = 2;
	curr_pos = file + exp->pos;
	sq_pos = ft_strchr(curr_pos + 1, 39);
	exp->word = ft_strjoin(exp->word,
			ft_substr(curr_pos, 0, sq_pos - curr_pos));
	exp->pos += sq_pos - curr_pos;
}

void	expand_inside_double_quote(t_expand *exp, char *file)
{
	char	*dq_pos;
	char	*curr_pos;
	char	*dollar_pos;

	exp->stat = 1;
	curr_pos = file + exp->pos;
	dq_pos = ft_strchr(curr_pos + 1, 34);
	while (*curr_pos && curr_pos < dq_pos)
	{
		dollar_pos = ft_strnchr(curr_pos, '$', dq_pos - curr_pos);
		if (!dollar_pos)
		{
			exp->word = ft_strjoin(exp->word,
					ft_substr(curr_pos, 0, dq_pos - curr_pos));
			break ;
		}
		exp->word = ft_strjoin(exp->word,
				ft_substr(curr_pos, 0, dollar_pos - curr_pos));
		exp->word = ft_strjoin(exp->word, get_env_name(dollar_pos));
		curr_pos = skip_env_var(dollar_pos + 1);
	}
	exp->pos += dq_pos - file - exp->pos;
}

void	expand_unquoted(t_expand *exp, char *file)
{
	char	*dollar_pos;
	char	*curr_pos;
	char	*q_pos;

	exp->stat = 0;
	curr_pos = file + exp->pos;
	q_pos = first_quote_occ(curr_pos + 1);
	if (!q_pos)
		q_pos = ft_strchr(curr_pos + 1, '\0');
	while (*curr_pos && curr_pos < q_pos)
	{
		dollar_pos = ft_strnchr(curr_pos, '$', q_pos - curr_pos);
		if (!dollar_pos)
		{
			exp->word = ft_strjoin(exp->word,
					ft_substr(curr_pos, 0, q_pos - curr_pos));
			break ;
		}
		exp->word = ft_strjoin(exp->word,
				ft_substr(curr_pos, 0, dollar_pos - curr_pos));
		exp->word = ft_strjoin(exp->word, get_env_name(dollar_pos));
		curr_pos = skip_env_var(dollar_pos + 1);
	}
	exp->pos += q_pos - file - exp->pos;
}

char	*first_quote_occ(char *str)
{
	char	*sq_pos;
	char	*dq_pos;

	sq_pos = ft_strchr(str, 39);
	dq_pos = ft_strchr(str, 34);
	if (sq_pos && dq_pos)
	{
		if (sq_pos < dq_pos)
			return (sq_pos);
		return (dq_pos);
	}
	if (!sq_pos)
		return (dq_pos);
	return (sq_pos);
}
