/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:03 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/18 18:54:02 by hfegrach         ###   ########.fr       */
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
		clean_and_exit(*get_status_code());
	}
}
