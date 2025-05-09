#include "gc.h"
// #include "../include/minishell.h"

t_gc **get_gc_head(void)
{
    static t_gc *head;

    return (&head);
}

