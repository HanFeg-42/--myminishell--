/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:51:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/12 23:03:36 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

//=============pathname expansion=================================

char	**remove_hidden_files(char **files)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	ret = NULL;
	ret = gc_alloc(sizeof(char *) * (hidden_file_size(files) + 1));
	j = 0;
	i = 0;
	while (files[i])
	{
		if (files[i][0] != '.' && ft_strncmp(files[i], "/.", 2))
			ret[j++] = ft_strdup(files[i]);
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

int	hidden_file_size(char **files)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (files[i])
	{
		if (files[i][0] != '.' && ft_strncmp(files[i], "/.", 2))
			size++;
		i++;
	}
	return (size);
}

void	replace_unquoted_asterisk(t_expand *exp)
{
	int		i;
	int		stat;
	char	*tmp;
	t_arg	*curr;

	curr = exp->arg;
	while (curr)
	{
		tmp = curr->value;
		stat = 0;
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == '"' && stat == 0)
				stat = 1;
			else if ((tmp[i] == '"' && stat == 1) || (tmp[i] == '\'' && stat == 2))
				stat = 0;
			else if (tmp[i] == '\'' && stat == 0)
				stat = 2;
			else if (tmp[i] == '*' && stat == 0)
				tmp[i] = -3;
			i++;
		}
		curr = curr->next;
	}
}
