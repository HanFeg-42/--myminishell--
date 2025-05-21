/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:25 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/21 22:24:53 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

void	field_split(t_expand *exp)
{
	t_arg	*arg;

	exp->pos = 0;
	while ((arg = get_next_field(exp))) // norminette
		arg_add(&exp->arg, arg);
}

t_arg	*get_next_field(t_expand *exp)
{
	exp_skip_whitespaces(exp);// increment exp->pos & exp-> word = exp->word + exp->pos
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

	stat = 0; // 0 -> normal | 1 -> in double quote | 2 -> in single quote
	while (*s)
	{
		if (*s == 39 && !stat)
			stat = 2; // in single quote
		else if (*s == 34 && !stat)
			stat = 1; // in double quote
		else if ((*s == 34 && stat == 1) || (*s == 39 && stat == 2))
			stat = 0; // khrjt mn l quoted stat
		else if (ft_issapce(*s) && !stat) //  dirii is_ifs 7sn lik
			return (s); // found an ifs outside the quotes
		s++;
	}
	return (NULL);
}

void	arg_add(t_arg **head, t_arg *new)
{
	t_arg	*last;

	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_arg	*arg_create(char *value)
{
	t_arg	*new;

	if (!value)
		return (NULL);
	new = ft_malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}
