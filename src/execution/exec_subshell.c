/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:03 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/02 16:45:30 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	execute_subshell(t_ast *ast, t_pipe *pipeline)
{
	int	*fds;

	fds = NULL;
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
			fds = open_redirects(ast->redirect);
			close_redirect(fds, num_of_redirects(ast->redirect));
		}
		execute_compound(ast->first_child);
		exit(*get_status_code());
	}
}
