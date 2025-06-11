/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:12:37 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/11 20:32:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

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
				if (!append_to_array(&result, &i,
						ft_strdup(exp->arg->file[j])))
					return (NULL);
				j++;
			}
		}
		else if (!append_to_array(&result, &i,
				undo_char_changes(remove_quotes(exp->arg->value))))
			return (NULL);
		exp->arg = exp->arg->next;
	}
	return (result);
}

char	*remove_quotes(char *str)
{
	char	*ret;

	int (stat), (i), (j);
	ret = gc_alloc(sizeof(char) * (ft_strlen(str) + 1));
	stat = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 && stat == 0)
			stat = 1;
		else if ((str[i] == 34 && stat == 1) || (str[i] == 39 && stat == 2))
			stat = 0;
		else if (str[i] == 39 && stat == 0)
			stat = 2;
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	is_quoted(char *eof)
{
	return (ft_strchr(eof, 34) || ft_strchr(eof, 39));
}

char	*undo_char_changes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = 39;
		if (str[i] == -2)
			str[i] = 34;
		if (str[i] == -3)
			str[i] = '*';
		i++;
	}
	return (str);
}

int	append_to_array(char ***var, size_t *size, char *append)
{
	char	**arr;

	arr = NULL;
	arr = *var;
	arr = ft_realloc(arr, sizeof(char *) * (*size + 2));
	arr[(*size)++] = append;
	arr[*size] = NULL;
	*var = arr;
	return (true);
}
