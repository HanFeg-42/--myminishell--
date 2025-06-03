/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:01 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 19:35:24 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	expand(ast);
	cmd->pos = i;
	cmd->pipeline = pipeline;
	if (ast->args == NULL)
		return ;
	//if (ast->args)
	//{
	cmd->type = type_cmd(ast->args[0]);
	if (cmd->type != -1 && cmd->pipeline->num_of_cmds == 1)
	{
		if (!(*get_parser_check()))
		{
			*get_status_code() = 1;
			return ;
		}
		*get_status_code() = 0; // TODO: update exit status code after execution.
 		execute_single_built(cmd, ast);
		return ;
	}
	//}
	exec_cmd(ast, cmd);
}

void	dup_standars(t_cmd *cmd)
{
	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
}

void	restor_standars(t_cmd *cmd)
{
	dup2(cmd->saved_stdout, STDOUT_FILENO);
	dup2(cmd->saved_stdin, STDIN_FILENO);
}

void	execute_single_built(t_cmd *cmd, t_ast *ast)
{
	dup_standars(cmd);
	if (ast->redirect)
	{
		cmd->num_of_redirect = num_of_redirects(ast->redirect);
		cmd->fds = open_redirects(ast->redirect);
		if (!(*get_error_check()))
		{
			restor_standars(cmd);
			return ;
		}
		close_redirect(cmd->fds, cmd->num_of_redirect - 1);
	}
	execute_builtins(cmd->type, ast->args);
	restor_standars(cmd);
}
