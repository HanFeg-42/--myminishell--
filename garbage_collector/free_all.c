#include "gc.h"

void free_all(void)
{
	t_gc **head;
	t_gc *curr;
	t_gc *next;

	head = get_gc_head();
	if (!head)
		return ;
	curr = *head;
	while (curr)
	{
		curr->prev = NULL;
		next = curr->next;
		if (curr->addr)
			free(curr->addr);
		free(curr);
		curr = next;
	}
	*head = NULL;
}
