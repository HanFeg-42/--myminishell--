/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:51:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 22:07:56 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

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
	new = gc_alloc(sizeof(t_arg));
	new->value = value;
	new->file = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
