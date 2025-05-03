#include "gc.h"

void gc_detach(t_gc *node)
{
    t_gc **head;
	
	head = get_gc_head();

    if (node->prev)
        node->prev->next = node->next;
    else
        *head = node->next;
    if (node->next)
	{
        node->next->prev = node->prev;
	}
	free(node->addr);
	free(node);
}


void free_one(void *addr)
{
    t_gc **head = get_gc_head();
    t_gc *curr;

    if (!head || !addr)
        return;

    curr = *head;
    while (curr)
    {
        if (curr->addr == addr)
        {
            gc_detach(curr);
            return;
        }
        curr = curr->next;
    }
}
