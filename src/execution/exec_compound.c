/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:56 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/02 16:03:48 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	*get_status_code(void)
{
	static int	status;

	return (&status);
}

void	advince_twice(t_ast **current)
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
	if ((*current)->type == AST_OR)
	{
		ast_advance(current);
		if (!(*get_status_code()))
		{
			ast_advance(current);
			while ((*current) && (*current)->type == AST_OR)
			{
				advince_twice(current);
			}
		}
	}
	if (*current && (*current)->type == AST_AND)
	{
		ast_advance(current);
		if (*get_status_code())
		{
			ast_advance(current);
			while ((*current) && (*current)->type == AST_AND)
			{
				advince_twice(current);
			}
		}
	}
}

void	execute_compound(t_ast *ast)
{
	t_ast	*current;

	if (!ast || !(*get_parser_check()))
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
	}
}
