/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:03 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/13 16:07:10 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	execute_subshell(t_ast *ast, t_pipe *pipeline)
{
	pipeline->counter++;
	pipeline->pids[pipeline->counter] = fork();
	if (pipeline->pids[pipeline->counter] < 0)
	{
		set_exec_error("fork", 1);
		return ;
	}
	if (pipeline->pids[pipeline->counter] == 0)
	{
		*get_status_code() = 0;
		if (ast->redirect)
		{
			open_redirects(ast->redirect);
		}
		execute_compound(ast->first_child);
		exit(*get_status_code());
	}
}
