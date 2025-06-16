/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_standards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:05:41 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 23:25:20 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	restore_stdin(t_pipe *pipeline)
{
	if (pipeline->saved_stdin >= 0)
	{
		dup2(pipeline->saved_stdin, STDIN_FILENO);
		close(pipeline->saved_stdin);
	}
}

void	dup_standards(t_cmd *cmd)
{
	cmd->saved_stdin = dup(STDIN_FILENO);
	cmd->saved_stdout = dup(STDOUT_FILENO);
	if (cmd->saved_stdin < 0 || cmd->saved_stdout < 0)
		set_exec_error("dup", 1);
}

void	restore_standards(t_cmd *cmd)
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
