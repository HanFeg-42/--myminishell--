/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:08:51 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/17 14:38:40 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	update_size(t_arg *arg, size_t *size)
{
	int	j;

	*size = 0;
	while (arg)
	{
		if (arg->file)
		{
			j = 0;
			while (arg->file[j])
			{
				(*size)++;
				j++;
			}
		}
		else
			(*size)++;
		arg = arg->next;
	}
}

size_t	get_dir_size(char *path)
{
	struct dirent	*entry;
	DIR				*dir;
	size_t			size;

	dir = opendir(path);
	size = 0;
	entry = readdir(dir);
	while (entry)
	{
		size++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (size);
}
