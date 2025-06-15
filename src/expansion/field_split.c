/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:25 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 23:23:21 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	exp_skip_ifs(t_expand *exp)
{
	while (is_ifs(*exp->word))
		exp->word++;
}

static char	*first_ifs_occ(char *s)
{
	int	stat;

	stat = NORMAL;
	while (*s)
	{
		if (*s == '\'' && stat == NORMAL)
			stat = SINGLE_QUOTED;
		else if (*s == '"' && stat == NORMAL)
			stat = DOUBLE_QUOTED;
		else if ((*s == '"' && stat == DOUBLE_QUOTED)
			|| (*s == '\'' && stat == SINGLE_QUOTED))
			stat = NORMAL;
		else if (is_ifs(*s) && stat == NORMAL)
			return (s);
		s++;
	}
	return (NULL);
}

static char	*get_field(t_expand *exp)
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

static t_arg	*get_next_field(t_expand *exp)
{
	exp_skip_ifs(exp);
	return (arg_create(get_field(exp)));
}

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
