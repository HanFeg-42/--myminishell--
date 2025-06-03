/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/03 14:37:07 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	**new_ptr;

	if (!ptr)
		return (ft_malloc(size));
	new_ptr = ft_malloc(size);
	copy_ptr(ptr, new_ptr, size);
	free_old_ptr(ptr);
	return (new_ptr);
}

void	copy_ptr(char **ptr, char **new_ptr, int size)
{
	int	i;

	i = 0;
	while (ptr[i] && i < size - 1)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		i++;
	}
	new_ptr[i] = NULL;
}

void	free_old_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free_one(ptr[i]);
		i++;
	}
	free_one(ptr);
}
