#include "../include/minishell.h"

void free_one(void *addr)
{
	t_gc **gc_head;
	t_gc *current;
	t_gc *next;
	t_gc *prev;

	gc_head = get_gc_head();
	if (!addr || !gc_head)
		return ;
	current = *gc_head;
	while (current)
	{
		if (current->addr == addr)
		{
			next = current->next;
			prev = current->prev;
			free(current->addr);
			prev->next = next;
			next->prev = prev;
			return ;
		}
		current = current->next;
	}
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