/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:01 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/14 22:17:04 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void setup_only_redirect(t_file *redirect, t_cmd *cmd)
{
	dup_standards(cmd);
	cmd->num_of_redirect = num_of_redirects(redirect);
	cmd->fds = open_redirects(redirect);
	if (!(*get_error_check()))
	{
		restore_standards(cmd);
		return;
	}
	close_redirect(cmd->fds, cmd->num_of_redirect - 1);
	restore_standards(cmd);
}

void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
	t_cmd *cmd;

	cmd = gc_alloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	expand(ast);
	cmd->pos = i;
	cmd->pipeline = pipeline;
	if (ast->args == NULL)
	{
		if (ast->redirect)
			setup_only_redirect(ast->redirect, cmd);
		if (!(*get_error_check()))
			return;
		*get_status_code() = 0;
		return;
	}
	if (!(*get_parser_check()))
	{
		*get_status_code() = 1;
		return;
	}
	cmd->type = type_cmd(ast->args[0]);
	if (cmd->type != -1 && cmd->pipeline->num_of_cmds == 1)
	{
		*get_status_code() = execute_single_built(cmd, ast);
		return;
	}
	exec_cmd(ast, cmd);
}

void dup_standards(t_cmd *cmd)
{
	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
	if (cmd->saved_stdin < 0 || cmd->saved_stdout < 0)
		set_exec_error("dup", 1);
}

void restore_standards(t_cmd *cmd)
{
	if (cmd->saved_stdout >= 0)
	{
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		close(cmd->saved_stdout);
	}
	if (cmd->saved_stdin >= 0)
	{
		dup2(cmd->saved_stdin, STDIN_FILENO);
		close(cmd->saved_stdin);
	}
}

int execute_single_built(t_cmd *cmd, t_ast *ast)
{
	*get_status_code() = 0;
	dup_standards(cmd);
	if (ast->redirect)
	{
		cmd->num_of_redirect = num_of_redirects(ast->redirect);
		cmd->fds = open_redirects(ast->redirect);
		if (!(*get_error_check()))
		{
			restore_standards(cmd);
			return (*get_status_code());
		}
		close_redirect(cmd->fds, cmd->num_of_redirect - 1);
	}
	execute_builtins(cmd->type, ast->args);
	restore_standards(cmd);
	return (*get_status_code());
}
