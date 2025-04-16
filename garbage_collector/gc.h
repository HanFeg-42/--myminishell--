#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// garbage collector
typedef struct s_gc
{
	void				*addr;
	struct s_gc			*next;
	struct s_gc			*prev;
}						t_gc;

// ==================---------gc---------=============================
void			*ft_malloc(size_t size);
t_gc			**get_gc_head(void);
t_gc			*gc_new(void *content);
void			gc_addback(t_gc *new);
t_gc			*gc_last(t_gc *head);
void			gc_print(t_gc *head);
void			free_one(void *addr);
void			free_all(void);
void			free_mid_node(t_gc *node);
void			free_first_node(t_gc *node);
void			free_last_node(t_gc *node);
void			free_lonley_node(t_gc *node);

#endif