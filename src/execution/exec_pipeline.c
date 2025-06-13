/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:58 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/13 16:44:04 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void swap_pipes(t_pipe *pipeline)
{
	int *tmp;
	
	tmp = pipeline->prev_pipe;
	pipeline->prev_pipe = pipeline->curr_pipe;
	pipeline->curr_pipe = tmp;
}

void	execute_pipeline(t_ast *ast)
{
	t_pipe	*pipeline;
	t_ast	*current;
	int		i;

	pipeline = init_pipeline(ast);
	if (!(*get_error_check()))
		return ;
	current = ast->first_child;
	i = 0;
	while (current)
	{
		execute_command(current, pipeline, i);
		swap_pipes(pipeline);
		ast_advance(&current);
		i++;
	}
	if (pipeline->num_of_cmds > 1)
		close_all_pipes(pipeline);
	wait_children(pipeline);
}

t_pipe	*init_pipeline(t_ast *ast)
{
	t_pipe	*pipeline;

	pipeline = gc_alloc(sizeof(t_pipe));
	pipeline->num_of_cmds = ast_size(ast);
	if (pipeline->num_of_cmds > 1)
	{
		pipeline->curr_pipe = gc_alloc(sizeof(int) * 2);
		pipeline->prev_pipe = gc_alloc(sizeof(int) * 2);
		if (pipe(pipeline->prev_pipe) < 0 || pipe(pipeline->curr_pipe) < 0)
			set_exec_error("pipe", 1);
	}
	pipeline->pids = gc_alloc(sizeof(int) * pipeline->num_of_cmds);
	pipeline->counter = -1;
	return (pipeline);
}


int	ast_size(t_ast *ast)
{
	int		i;
	t_ast	*current;

	current = ast->first_child;
	i = 0;
	while (current)
	{
		current = current->next_sibling;
		i++;
	}
	return (i);
}
