/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:12:37 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/16 18:07:15 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	erase(char *str, size_t i)
{
	if (i >= ft_strlen(str) || !str)
		return ;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}

char	*remove_quotes(char *str)
{
	bool	is_single;
	bool	is_double;
	size_t	i;

	is_single = false;
	is_double = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_single)
		{
			erase(str, i);
			is_double = !is_double;
			continue ;
		}
		if (str[i] == '\'' && !is_double)
		{
			erase(str, i);
			is_single = !is_single;
			continue ;
		}
		i++;
	}
	return (str);
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
	// arr = ft_realloc(arr, sizeof(char *) * (*size + 2));
	arr[(*size)++] = append;
	arr[*size] = NULL;
	*var = arr;
}
void update_sizes(t_arg *arg, size_t *size)
{
	int j;
	*size = 0;
	while (arg)
	{
		if (arg->file)
		{
			j = 0;
			while (arg->file[j])
				(*size)++;
		}
		else
			(*size)++;
		arg = arg->next;
	}
}
char	**remove_quotes_from_all(t_expand *exp)
{
	char	**result;
	size_t	size;
	size_t	j;

	result = NULL;
	update_sizes(exp->arg, &size);
	result = gc_alloc(sizeof(char *) * (size + 1));
	size = 0;
	while (exp->arg)
	{
		if (exp->arg->file)
		{
			j = 0;
			while (exp->arg->file[j])
			{
				append_to_array(&result, &size,
					ft_strdup(exp->arg->file[j]));
				j++;
			}
		}
		else
			append_to_array(&result, &size,
				undo_char_changes(remove_quotes(exp->arg->value)));
		exp->arg = exp->arg->next;
	}
	return (result);
}
