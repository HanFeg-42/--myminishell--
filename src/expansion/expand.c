/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:00:42 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/16 18:28:47 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

// TODO : change the logic of append_to_array so that it doesn't  realloc simultanuously

t_expand	*init_expand(char **args)
{
	t_expand	*exp;

	exp = gc_alloc(sizeof(t_expand));
	exp->arg = NULL;
	exp->args = copy_arr(args);
	exp->i = 0;
	exp->stat = 0;
	exp->pos = 0;
	// exp->cwd_files = get_cwd_files();
	return (exp);
}

char	**expander(char **args)
{
	t_expand	*expand;

	if (!args)
		return (NULL);
	expand = init_expand(args);
	while (expand && expand->args && expand->args[expand->i])
	{
		expand_parameter(expand);
		field_split(expand);
		expand->i++;
	}
	expand_pathname(expand);
	return (remove_quotes_from_all(expand));
}

void	expand(t_ast *ast)
{
	*get_parser_check() = true;
	ast->args = expander(ast->args);
	expand_file(ast->redirect);
}
