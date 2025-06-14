/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:58 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/14 21:18:01 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	close_pipe(int *pipefd)
{
	if (!pipefd)
		return;
	close(pipefd[0]);
	close(pipefd[1]);
}


t_pipe *init_pipeline(t_ast *ast)
{
	t_pipe *pipeline;

	pipeline = gc_alloc(sizeof(t_pipe));
	ft_memset(pipeline, 0, sizeof(t_pipe));
	pipeline->num_of_cmds = ast_size(ast);
	pipeline->counter = -1;
	pipeline->saved_stdin = dup(STDIN_FILENO);
	if (pipeline->saved_stdin < 0)
		set_exec_error("dup", 1);
	if (pipeline->num_of_cmds > 1)
	{
		pipeline->pipefd = gc_alloc(sizeof(int) * 2);
		if (pipe(pipeline->pipefd) < 0)
			set_exec_error("pipe", 1);
	}
	pipeline->pids = gc_alloc(sizeof(int) * pipeline->num_of_cmds);
	return (pipeline);
}

void execute_pipeline(t_ast *ast)
{
	t_pipe *pipeline;
	t_ast *current;
	int i;

	pipeline = init_pipeline(ast);
	if (!(*get_error_check()))
		return;
	current = ast->first_child;
	i = 0;
	while (current)
	{
		execute_command(current, pipeline, i);
		if(++i < pipeline->num_of_cmds -1 )
		{
			dup2(pipeline->pipefd[0],0);
			close_pipe(pipeline->pipefd);
			if (pipe(pipeline->pipefd) < 0)
			{
				set_exec_error("pipe", 1);
				break ;
			}
		}
		ast_advance(&current);
	}
	if (pipeline->num_of_cmds > 1)
		close_pipe(pipeline->pipefd);
	if (pipeline->saved_stdin >= 0)
	{
		dup2(pipeline->saved_stdin, STDIN_FILENO);
		close(pipeline->saved_stdin);
	}
	wait_children(pipeline);
}

int ast_size(t_ast *ast)
{
	int i;
	t_ast *current;

	current = ast->first_child;
	i = 0;
	while (current)
	{
		current = current->next_sibling;
		i++;
	}
	return (i);
}
