/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:25 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/27 19:59:25 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

void	field_split(t_expand *exp)
{
	t_arg	*arg;

	exp->pos = 0;
	arg = get_next_field(exp);
	while (arg)
	{
		arg_add(&exp->arg, arg);
		arg = get_next_field(exp);
	}
}

t_arg	*get_next_field(t_expand *exp)
{
	exp_skip_whitespaces(exp);
	return (arg_create(get_field(exp)));
}

void	exp_skip_whitespaces(t_expand *exp)
{
	while (ft_issapce(*exp->word))
		exp->word++;
}

char	*get_field(t_expand *exp)
{
	char	*ret;
	char	*ifs_pos;

	if (!exp->word || !(*exp->word))
		return (NULL);
	ifs_pos = first_ifs_occ(exp->word);
	if (!ifs_pos)
	{
		ret = ft_strdup(exp->word);
		*exp->word = '\0';
		return (ret);
	}
	ret = ft_substr(exp->word, 0, ifs_pos - exp->word);
	exp->word = ifs_pos;
	return (ret);
}

char	*first_ifs_occ(char *s)
{
	int	stat;

	stat = 0;
	while (*s)
	{
		if (*s == 39 && !stat)
			stat = 2;
		else if (*s == 34 && !stat)
			stat = 1;
		else if ((*s == 34 && stat == 1) || (*s == 39 && stat == 2))
			stat = 0;
		else if (ft_issapce(*s) && !stat)
			return (s);
		s++;
	}
	return (NULL);
}
