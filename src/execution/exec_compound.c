/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:56 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/12 16:04:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	*get_status_code(void)
{
	static int	status = 0;

	return (&status);
}

void	advance_twice(t_ast **current)
{
	ast_advance(current);
	ast_advance(current);
}

void	ast_advance(t_ast **current)
{
	if (*current)
		*current = (*current)->next_sibling;
}

void	and_or_handler(t_ast **current)
{
	t_ast_type	type;

	type = AST_OR;
	if (*get_status_code() > 0)
		type = AST_AND;
	while ((*current) && (*current)->type == type)
		advance_twice(current);
}

void	execute_compound(t_ast *ast)
{
	t_ast	*current;

	if (!ast)
		return ;
	current = ast->first_child;
	while (current)
	{
		execute_pipeline(current);
		if (!(*get_error_check()))
			return ;
		ast_advance(&current);
		if (current)
			and_or_handler(&current);
		ast_advance(&current);
	}
}
