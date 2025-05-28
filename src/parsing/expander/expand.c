/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:00:42 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 11:33:51 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

void	expand(t_ast *ast)
{
	*get_parser_check() = true;
	ast->args = expander(ast->args);
	expand_file(ast->redirect);
}

char	**expander(char **args)
{
	t_expand	*expand;

	if (!args)
		return (NULL);
	expand = init_expand(args);
	while (expand && expand->args && expand->args[expand->i])
	{
		expand_param(expand);
		field_split(expand);
		expand->i++;
	}
	expand_pathname(expand);
	return (remove_quotes_from_all(expand));
}

t_expand	*init_expand(char **args)
{
	t_expand	*exp;

	exp = ft_malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	exp->arg = NULL;
	exp->args = copy_arr(args);
	exp->i = 0;
	exp->stat = 0;
	exp->pos = 0;
	exp->dir_files = get_files();
	return (exp);
}
