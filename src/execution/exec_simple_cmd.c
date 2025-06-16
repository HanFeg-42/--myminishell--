/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:01 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 22:44:12 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	handle_empty_args(t_ast *ast, t_cmd *cmd)
{
	if (ast->redirect)
		setup_only_redirect(ast->redirect, cmd);
	if (!(*get_error_check()))
		return ;
	*get_status_code() = 0;
}

int	execute_single_built(t_cmd *cmd, t_ast *ast)
{
	dup_standards(cmd);
	if (ast->redirect)
	{
		open_redirects(ast->redirect);
		if (!(*get_error_check()))
		{
			restore_standards(cmd);
			return (*get_status_code());
		}
	}
	execute_builtins(cmd->type, ast->args);
	restore_standards(cmd);
	return (*get_status_code());
}

void	setup_only_redirect(t_file *redirect, t_cmd *cmd)
{
	dup_standards(cmd);
	open_redirects(redirect);
	if (!(*get_error_check()))
	{
		restore_standards(cmd);
		return ;
	}
	restore_standards(cmd);
}

void	execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
	t_cmd	*cmd;

	cmd = gc_alloc(sizeof(t_cmd));
	ft_memset(cmd, 0, sizeof(t_cmd));
	expand(ast);
	cmd->pos = i;
	cmd->pipeline = pipeline;
	if (!(*get_parser_check()))
	{
		*get_status_code() = 1;
		return ;
	}
	if (ast->args == NULL)
	{
		handle_empty_args(ast, cmd);
		return ;
	}
	cmd->type = type_cmd(ast->args[0]);
	if (cmd->type != -1 && cmd->pipeline->num_of_cmds == 1)
	{
		*get_status_code() = execute_single_built(cmd, ast);
		return ;
	}
	exec_cmd(ast, cmd);
}
