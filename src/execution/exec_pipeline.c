/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:58 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 23:09:51 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

t_pipe	*init_pipeline(t_ast *ast)
{
	t_pipe	*pipeline;

	pipeline = gc_alloc(sizeof(t_pipe));
	ft_memset(pipeline, 0, sizeof(t_pipe));
	pipeline->num_of_cmds = ast_size(ast);
	*get_num_cmds() = pipeline->num_of_cmds;
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

static void	handle_pipe(t_pipe *pipeline)
{
	dup2(pipeline->pipefd[0], STDIN_FILENO);
	close_pipe(pipeline->pipefd);
	if (pipe(pipeline->pipefd) < 0)
		set_exec_error("pipe", 1);
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
		if (i < pipeline->num_of_cmds - 1)
			handle_pipe(pipeline);
		if (!*get_error_check())
			break ;
		ast_advance(&current);
		i++;
	}
	if (pipeline->num_of_cmds > 1)
		close_pipe(pipeline->pipefd);
	restore_stdin(pipeline);
	wait_children(pipeline);
}

// void execute_pipeline(t_ast *ast)
// {
// 	t_pipe *pipeline;
// 	t_ast *current;
// 	int i;

// 	pipeline = init_pipeline(ast);
// 	if (!(*get_error_check()))
// 		return ;
// 	current = ast->first_child;
// 	i = 0;
// 	while (current)
// 	{
// 		execute_command(current, pipeline, i);
// 		if(i < pipeline->num_of_cmds -1 )
// 		{
// 			dup2(pipeline->pipefd[0],0);
// 			close_pipe(pipeline->pipefd);
// 			if (pipe(pipeline->pipefd) < 0)
// 			{
// 				set_exec_error("pipe", 1);
// 				break ;
// 			}
// 		}
// 		ast_advance(&current);
// 		i++;
// 	}
// 	if (pipeline->num_of_cmds > 1)
// 		close_pipe(pipeline->pipefd);
// 	if (pipeline->saved_stdin >= 0)
// 	{
// 		dup2(pipeline->saved_stdin, STDIN_FILENO);
// 		close(pipeline->saved_stdin);
// 	}
// 	wait_children(pipeline);
// }