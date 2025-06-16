/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:09 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 16:50:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void open_redirects(t_file *redirect)
{
	t_file	*current;
	int		fd;
	int		i;

	i = 0;
	current = redirect;
	while (current)
	{
		fd = open_file(current);
		if (!(*get_error_check()))
			return ;
		redirect_io(fd, current);
		close(fd);
		current = current->next;
	}
}

int	open_file(t_file *file)
{
	int fd;
	
	if (file->type == APPEND)
		fd = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		fd = open(file->filename, O_RDONLY);
	else
		fd = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		set_exec_error(file->filename, 1);

	printf("fd ---> %d \n\n\n",fd);
	return (fd);
}

void	redirect_io(int fd, t_file *file)
{
	if (file->type == APPEND || file->type == OUTPUT_RED)
		dup2(fd, STDOUT_FILENO);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:12 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/13 18:21:38 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	exec_cmd(t_ast *ast, t_cmd *cmd)
{ 
	cmd->pipeline->counter++;
	cmd->pipeline->pids[cmd->pipeline->counter] = fork();
	if (cmd->pipeline->pids[cmd->pipeline->counter] < 0)
	{
		set_exec_error("fork", 1);
		return ;
	}
	if (cmd->pipeline->pids[cmd->pipeline->counter] == 0)
	{
		//TODO: setup signals -> signal(SIGINT, SIG_DEF), signal(SIGQUIT, SIG_DEF), signal(SIGTERM, SIG_DEF)
		if (!(*get_parser_check()))
		{
			close_pipe(cmd->pipeline->curr_pipe);
			exit(EXIT_FAILURE);
		}
		handle_process(ast, cmd);
	}
	signal(SIGINT, SIG_IGN);
}

void	handle_process(t_ast *ast, t_cmd *cmd)
{
	setup_process_pipes(cmd->pipeline, cmd->pos);
	setup_redirects(ast);
	// if (!ast->args)
	// {
	// 	clean_and_exit();
	// 	exit(EXIT_SUCCESS);
	// }
	cmd->type = type_cmd(ast->args[0]);
	if (cmd->type != -1)
	{
		execute_builtins(cmd->type, ast->args);
		clean_and_exit();
		exit(*get_status_code());
	}
	cmd->envp = convert_envp();
	cmd->pathname = get_path(ast->args[0], cmd->envp);
	if (!cmd->pathname)
		handle_cmd_error(ast->args[0]);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->pathname, ast->args, cmd->envp);
	clean_and_exit();
	exit(126);
}

int	type_cmd(char *cmd)
{
	char	*command;
	char	*position;

	command = ft_strdup(cmd);
	position = ft_strrchr(cmd, '/');
	if (position)
	{
		command = ft_strdup(position + 1);
	}
	return (is_builtin(command));
}

void	setup_redirects(t_ast *ast)
{
	if (ast->redirect)
	{
		open_redirects(ast->redirect);
		if (!(*get_error_check()))
		{
			clean_and_exit();
			exit(1);
		}
	}
}

void	setup_process_pipes(t_pipe *pipeline, int i)
{
	if (pipeline->num_of_cmds > 1)
	{
		if (i == 0)
		{
			dup2(pipeline->curr_pipe[1], STDOUT_FILENO);
		}
		else if (i == pipeline->num_of_cmds - 1)
		{
			dup2(pipeline->prev_pipe[0], STDIN_FILENO);
		}
		else
		{
			dup2(pipeline->prev_pipe[0], STDIN_FILENO);
			dup2(pipeline->curr_pipe[1], STDOUT_FILENO);
		}
		close_allpipes(pipeline);
	}
}



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
