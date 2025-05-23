/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 11:30:18 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gc.h"

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	gc_addback(gc_new(ret));
	return (ret);
}

t_gc	*gc_new(void *content)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		return (NULL);
	new->addr = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	gc_addback(t_gc *new)
{
	t_gc	*last;
	t_gc	**head;

	head = get_gc_head();
	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = gc_last(*head);
	last->next = new;
	new->prev = last;
}

t_gc	*gc_last(t_gc *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	gc_print(t_gc *head)
{
	while (head)
	{
		printf("node = %p\tvalue = %p\tnext = %p\tprev = %p\n",
			head, head->addr, head->next, head->prev);
		head = head->next;
	}
}
