/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:12 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/15 16:55:06 by gstitou          ###   ########.fr       */
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
		if (!(*get_parser_check()))
		{
			close_pipe(cmd->pipeline->pipefd);
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
	if (!ast->args)
		clean_and_exit(EXIT_SUCCESS);
	cmd->type = type_cmd(ast->args[0]);
	if (cmd->type != -1)
	{
		execute_builtins(cmd->type, ast->args);
		clean_and_exit(*get_status_code());
	}
	cmd->envp = convert_envp();
	cmd->pathname = get_path(ast->args[0], cmd->envp);
	if (!cmd->pathname)
		handle_cmd_error(ast->args[0]);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->pathname, ast->args, cmd->envp);
	clean_and_exit(126);
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
			clean_and_exit(1);
	}
}

void	setup_process_pipes(t_pipe *pipeline, int i)
{
	if (pipeline->num_of_cmds > 1)
	{
		if (i == 0)
		{
			dup2(pipeline->pipefd[1], STDOUT_FILENO);
		}
		else if (i < pipeline->num_of_cmds - 1)
		{
			dup2(pipeline->pipefd[1], STDOUT_FILENO);
		}
		close_pipe(pipeline->pipefd);
		close(pipeline->saved_stdin);
	}
}
