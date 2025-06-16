/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/16 18:25:13 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	track_positions(char **star, char **p_pos, char **s, char **p)
{
	if (*(*p) == STAR)
	{
		(*star) = (*p)++;
		(*p_pos) = *s;
	}
	else
	{
		(*p)++;
		(*s)++;
	}
}

static int	is_match(char *filename, char *pattern)
{
	char	*asterisk;
	char	*track_pos;

	asterisk = NULL;
	track_pos = NULL;
	while (*filename)
	{
		if (*pattern == *filename || *pattern == STAR)
			track_positions(&asterisk, &track_pos, &filename, &pattern);
		else if (asterisk)
		{
			pattern = asterisk + 1;
			filename = ++track_pos;
		}
		else
			return (0);
	}
	while (*pattern == STAR)
		pattern++;
	return (*pattern == '\0');
}

static void	arg_traversal(t_expand *exp, t_arg *arg)
{
	int			i;
	size_t		size;
	char		**files;

	files = get_files(exp, arg);
	if (!files)
		return ;
	i = 0;
	size = 0;
	while (files[i])
	{
		if (is_match(files[i], remove_quotes(arg->value)))
			size++;
		i++;
	}
	if (!size)
		return ;
	arg->file = gc_alloc(sizeof(char *) * (size + 1));
	i = 0;
	size = 0;
	while (files[i])
	{
		if (is_match(files[i], remove_quotes(arg->value)))
			append_to_array(&arg->file, &size, ft_strdup(files[i]));
		i++;
	}
}

void	expand_pathname(t_expand *exp)
{
	t_arg	*arg;

	replace_unquoted_asterisk(exp);
	arg = exp->arg;
	while (arg)
	{
		if (ft_strchr(arg->value, STAR)
			&& (arg->prev == NULL
				|| (arg->prev != NULL
					&& arg->prev->value != NULL
					&& ft_strcmp("export", arg->prev->value))))
			arg_traversal(exp, arg);
		arg = arg->next;
	}
}
