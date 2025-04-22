#include "gc.h"

void free_one(void *addr)
{
	t_gc **head;
	t_gc *curr;

	head = get_gc_head();
	if (!head || !addr)
		return ;
	curr = *head;
	while (curr)
	{
		if (curr->addr == addr)
		{
			if (curr->prev && curr->next)
				free_mid_node(curr);
			else if (!curr->prev && curr->next)
				free_first_node(curr);
			else if (curr->prev && !curr->next)
				free_last_node(curr);
			else
				free_lonley_node(curr);
			return ;
		}
		curr = curr->next;
	}
}

void free_mid_node(t_gc *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node->addr);
	free(node);
}

void free_first_node(t_gc *node)
{
	*get_gc_head() = node->next;
	(*get_gc_head())->prev = NULL;
	// node->next->prev = NULL;
	free(node->addr);
	free(node);
}

void free_last_node(t_gc *node)
{
	node->prev->next = NULL;
	free(node->addr);
	free(node);
}

void free_lonley_node(t_gc *node)
{
	free(node->addr);
	free(node);
	*get_gc_head() = NULL;
}
