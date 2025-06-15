/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:04:29 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 22:29:47 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	paramter_expansion(char *file, t_expand *exp)
{
	exp->word = ft_strdup("");
	while (exp->pos < (int)ft_strlen(file) && file[exp->pos])
	{
		if (file[exp->pos] == '"' && exp->stat == NORMAL)
			expand_inside_double_quote(exp, file);
		else if (file[exp->pos] == '\'' && exp->stat == NORMAL)
			copy_characters_until_quote(exp, file);
		else
			expand_unquoted(exp, file);
	}
}

static int	field_splitting(t_expand *exp)
{
	exp->arg = NULL;
	field_split(exp);
	return ((exp->arg) && (!ft_strcmp(exp->arg->value, "")
			|| exp->arg->next));
}

static int	pathname_expansion(t_expand *exp)
{
	expand_pathname(exp);
	return (!(exp->arg && exp->arg->file
			&& (!ft_strcmp(exp->arg->file[0], "")
				|| exp->arg->file[1])));
}

static void	ambiguous_redirect(char *err)
{
	*(get_parser_check()) = false;
	if (err)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}

void	expand_file(t_file *red)
{
	t_expand	*exp;
	t_file		*tmp;

	if (!red)
		return ;
	tmp = red;
	exp = init_expand(NULL);
	while (red)
	{
		paramter_expansion(red->filename, exp);
		if (field_splitting(exp) || !pathname_expansion(exp) || !exp->arg)
			return (ambiguous_redirect(red->filename));
		if (exp->arg->file)
			red->filename = undo_char_changes(remove_quotes(exp->arg->file[0]));
		else
			red->filename = undo_char_changes(remove_quotes(exp->arg->value));
		red = red->next;
	}
	red = tmp;
}
