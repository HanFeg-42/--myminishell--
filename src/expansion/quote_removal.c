/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:12:37 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 01:30:47 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*remove_quotes(char *str)
{
	char	*ret;

	int (stat), (i), (j);
	ret = gc_alloc(sizeof(char) * (ft_strlen(str) + 1));
	stat = NORMAL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && stat == NORMAL)
			stat = DOUBLE_QUOTED;
		else if ((str[i] == '"' && stat == DOUBLE_QUOTED)
			|| (str[i] == '\'' && stat == SINGLE_QUOTED))
			stat = NORMAL;
		else if (str[i] == '\'' && stat == NORMAL)
			stat = SINGLE_QUOTED;
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*undo_char_changes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SQ)
			str[i] = '\'';
		if (str[i] == DQ)
			str[i] = '"';
		if (str[i] == STAR)
			str[i] = '*';
		i++;
	}
	return (str);
}

void	append_to_array(char ***var, size_t *size, char *append)
{
	char	**arr;

	arr = NULL;
	arr = *var;
	arr = ft_realloc(arr, sizeof(char *) * (*size + 2));
	arr[(*size)++] = append;
	arr[*size] = NULL;
	*var = arr;
}
// zakaiahanana\0\0
void	erase(char *str, size_t i)
{
	if (i >= ft_strlen(str) || !str)
		return ;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}
// while (str[i])
/*
is_double ; is_single;
{
	if (str[i] == '"' && !is_double)
	{
		erase(str[i], i); is_double = true; continue;
	}
	// 
	i++;
}*/
char	**remove_quotes_from_all(t_expand *exp)
{
	char	**result;
	size_t	i;
	size_t	j;

	i = 0;
	result = NULL;
	while (exp->arg)
	{
		if (exp->arg->file)
		{
			j = 0;
			while (exp->arg->file[j])
			{
				append_to_array(&result, &i,
					ft_strdup(exp->arg->file[j]));
				j++;
			}
		}
		else
			append_to_array(&result, &i,
				undo_char_changes(remove_quotes(exp->arg->value)));
		exp->arg = exp->arg->next;
	}
	return (result);
}
