/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:36 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 16:43:05 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	close_all_pipes(t_pipe *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->num_of_cmds - 1)
	{
		close(pipeline->pipes[i][0]);
		close(pipeline->pipes[i][1]);
		i++;
	}
}

void	cleanup_process(t_ast *ast, t_cmd *cmd)
{
	if (ast->redirect)
		close_redirect(cmd->fds, cmd->num_of_redirect - 1);
	free_all_env(get_env_head());
	free_all();
}

void	wait_children(t_pipe *pipeline)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pipeline->counter)
	{
		waitpid(pipeline->pids[i], &status, 0);
		if (i == pipeline->counter)
		{
			if (WIFEXITED(status))
				*get_status_code() = WEXITSTATUS(status);
		}
		i++;
	}
	if (WIFSIGNALED(status)
		&& (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		*get_status_code() = 128 + WTERMSIG(status);
	}
}

void	free_all_env(t_envp **envp)
{
	t_envp	*current;

	current = *envp;
	while (*envp)
	{
		if ((*envp)->key)
			free((*envp)->key);
		if ((*envp)->value)
			free((*envp)->value);
		current = *envp;
		*envp = (*envp)->next;
		free(current);
	}
}

void	clean_and_exit(char *str, int nb)
{
	if (str)
		perror(str);
	free_all_env(get_env_head());
	free_all();
	exit(nb);
}
