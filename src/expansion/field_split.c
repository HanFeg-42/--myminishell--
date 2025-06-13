/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:25 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/12 23:03:59 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

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
	if (!ifs_pos || (exp->i > 0 && exp->args[exp->i - 1]
			&& !ft_strcmp("export", exp->args[exp->i - 1])))
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
		if (*s == '\'' && !stat)
			stat = 2;
		else if (*s == '"' && !stat)
			stat = 1;
		else if ((*s == '"' && stat == 1) || (*s == '\'' && stat == 2))
			stat = 0;
		else if (ft_issapce(*s) && !stat)
			return (s);
		s++;
	}
	return (NULL);
}
