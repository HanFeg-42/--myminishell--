/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:04:29 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 14:53:52 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

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

//==============PARAMETER EXPANSION==================
void	paramter_expansion(char *file, t_expand *exp)
{
	exp->word = ft_strdup("");
	while (exp->pos < (int)ft_strlen(file) && file[exp->pos])
	{
		if (file[exp->pos] == 34 && exp->stat == 0)
			expand_inside_double_quote(exp, file);
		else if ((file[exp->pos] == 34 && exp->stat == 1)
			|| (file[exp->pos] == 39 && exp->stat == 2))
			expand_unquoted(exp, file);
		else if (file[exp->pos] == 39 && exp->stat == 0)
			copy_characters_until_quote(exp, file);
		else
			expand_unquoted(exp, file);
	}
}

//====================FIELD SPLITTING=====================
int	field_splitting(t_expand *exp)
{
	exp->arg = NULL;
	field_split(exp);
	if ((exp->arg) && (!ft_strcmp(exp->arg->value, "")
			|| exp->arg->next))
		return (true);
	return (false);
}

//===================PATHNAME EXPANSION===================
int	pathname_expansion(t_expand *exp)
{
	expand_pathname(exp);
	if (exp->arg && exp->arg->file
		&& (!ft_strcmp(exp->arg->file[0], "")
			|| exp->arg->file[1]))
		return (false);
	return (true);
}

//===================AMBIGUOUS REDIRECT===================
void	ambiguous_redirect(char *err)
{
	*(get_parser_check()) = false;
	if (err)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}
