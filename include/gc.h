/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:59 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/11 20:32:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

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
void			*gc_alloc(size_t size);
t_gc			**get_gc_head(void);
t_gc			*gc_new(void *content);
void			gc_addback(t_gc *new);
t_gc			*gc_last(t_gc *head);
void			gc_print(t_gc *head);
void			free_one(void *addr);
void			free_all(void);
void			gc_detach(t_gc *node);

#endif