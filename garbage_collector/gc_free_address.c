/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_address.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:49 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 16:28:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"

static void	gc_detach(t_gc *node)
{
	t_gc	**head;

	head = get_gc_head();
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->addr);
	free(node);
}

void	free_one(void *addr)
{
	t_gc	**head;
	t_gc	*curr;

	head = get_gc_head();
	if (!head || !addr)
		return ;
	curr = *head;
	while (curr)
	{
		if (curr->addr == addr)
		{
			gc_detach(curr);
			return ;
		}
		curr = curr->next;
	}
}
