/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:09:40 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 23:10:20 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	ast_size(t_ast *ast)
{
	int		i;
	t_ast	*current;

	current = ast->first_child;
	i = 0;
	while (current)
	{
		current = current->next_sibling;
		i++;
	}
	return (i);
}
