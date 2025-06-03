/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:58 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 19:30:04 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	execute_pipeline(t_ast *ast)
{
	t_pipe	*pipeline;
	t_ast	*current;
	int		i;

	pipeline = init_pipes(ast);
	create_pipes(pipeline);
	if (!(*get_error_check()))
		return ;
	current = ast->first_child;
	i = 0;
	while (current)
	{
		execute_command(current, pipeline, i);
		ast_advance(&current);
		i++;
	}
	close_all_pipes(pipeline);
	wait_children(pipeline);
}

void	alloc_pipe_fds(t_pipe *pipeline)
{
	int	i;

	i = 0;
	pipeline->pipes = ft_malloc(sizeof(int *) * (pipeline->num_of_cmds - 1));
	while (i < pipeline->num_of_cmds - 1)
	{
		pipeline->pipes[i] = ft_malloc(sizeof(int) * 2);
		i++;
	}
}

t_pipe	*init_pipes(t_ast *ast)
{
	t_pipe	*pipeline;

	pipeline = ft_malloc(sizeof(t_pipe));
	pipeline->num_of_cmds = ast_size(ast);
	// printf("%d\n", pipeline->num_of_cmds );
	//if (pipeline->num_of_cmds > 1)
	alloc_pipe_fds(pipeline);
	pipeline->pids = ft_malloc(sizeof(int) * pipeline->num_of_cmds);
	pipeline->counter = -1;
	return (pipeline);
}

void	create_pipes(t_pipe *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->num_of_cmds - 1)
	{
		if (pipe(pipeline->pipes[i]) < 0)
			set_exec_error("pipe", 1);
		i++;
	}
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
