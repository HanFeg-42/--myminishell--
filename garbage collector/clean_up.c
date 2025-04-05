#include "../include/minishell.h"

void free_one(void *addr)
{
	t_gc **gc_head;
	t_gc *current;

	gc_head = get_gc_head();
	if (!addr || !gc_head)
		return ;
	current = *gc_head;
	while (current)
	{
		if (current->addr == addr)
		{
			if (*gc_head == current)
				free_head();
			else if (!current->next)
				free_last();
			else
				free_middle(current);
			return ;
		}
		current = current->next;
	}
}

void free_head(void)
{
	t_gc *gc_head;

	gc_head = *get_gc_head();
	gc_head = gc_head->next;
	free(gc_head->prev->addr);
	gc_head->prev = NULL;
}

void free_last(void)
{
	t_gc	*last;

	last = gc_last(*get_gc_head);
	last->prev->next = NULL;
	free(last->addr);
}

void free_middle(t_gc *element)
{
	t_gc *next;
	t_gc *prev;

	next = element->next;
	prev = element->prev;
	free(element->addr);
	prev->next = next;
	next->prev = prev;
}


void free_all(void)
{
	t_gc **gc_head;
	t_gc *current;

	gc_head = get_gc_head();
	if (!gc_head)
		return ;
	current = *gc_head;
	while (current)
	{
		free_one(current->addr);
		current = current->next;
	}
}
