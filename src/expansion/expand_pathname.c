/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/17 13:03:28 by hfegrach         ###   ########.fr       */
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
	char		**files;
	size_t		index[2];

	files = get_files(exp, arg);
	if (!files)
		return ;
	ft_memset(index, 0, sizeof(index));
	while (files[index[0]])
	{
		if (is_match(files[index[0]], remove_quotes(arg->value)))
			index[1]++;
		index[0]++;
	}
	if (!index[1])
		return ;
	arg->file = gc_alloc(sizeof(char *) * (index[1] + 1));
	ft_memset(index, 0, sizeof(index));
	while (files[index[0]])
	{
		if (is_match(files[index[0]], remove_quotes(arg->value)))
			append_to_array(&arg->file, &index[1], ft_strdup(files[index[0]]));
		index[0]++;
	}
}
// TODO : change ythe codition so that it checks exp->arg->value instead of dak tkhrbiq
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
