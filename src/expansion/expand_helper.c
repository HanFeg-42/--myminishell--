/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:51:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 22:36:24 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	hidden_file_size(char **files)
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

char	**copy_arr(char **arg)
{
	char	**ret;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
		i++;
	ret = gc_alloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arg[i])
	{
		ret[i] = ft_strdup(arg[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	replace_unquoted_asterisk(t_expand *exp)
{
	int		i;
	int		stat;
	t_arg	*curr;

	curr = exp->arg;
	while (curr)
	{
		stat = NORMAL;
		i = 0;
		while (curr->value[i])
		{
			if (curr->value[i] == '"' && stat == NORMAL)
				stat = DOUBLE_QUOTED;
			else if ((curr->value[i] == '"' && stat == DOUBLE_QUOTED)
				|| (curr->value[i] == '\'' && stat == SINGLE_QUOTED))
				stat = NORMAL;
			else if (curr->value[i] == '\'' && stat == NORMAL)
				stat = SINGLE_QUOTED;
			else if (curr->value[i] == '*' && stat == NORMAL)
				curr->value[i] = STAR;
			i++;
		}
		curr = curr->next;
	}
}

char	*first_quote_occ(char *str)
{
	char	*sq_pos;
	char	*dq_pos;

	sq_pos = ft_strchr(str, '\'');
	dq_pos = ft_strchr(str, '"');
	if (sq_pos && dq_pos)
	{
		if (sq_pos < dq_pos)
			return (sq_pos);
		return (dq_pos);
	}
	if (!sq_pos)
		return (dq_pos);
	return (sq_pos);
}
