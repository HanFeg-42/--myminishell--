/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:36 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/13 20:29:59 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	close_all_pipes(t_pipe *pipeline)
{
	
	close(pipeline->prev_pipe[0]);
	close(pipeline->prev_pipe[1]);
	close(pipeline->curr_pipe[0]);
	close(pipeline->curr_pipe[1]);
}

void	cleanup()
{
	if (*saved_pwd())
		free(*saved_pwd());
	free_all_env(get_env_head());
	free_all();
}

void	wait_children(t_pipe *pipeline)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (pipeline->counter == -1)
		return ;
	waitpid(pipeline->pids[pipeline->counter], &status, 0);
	while (i < pipeline->counter)
	{
		wait(NULL);
		i++;
	}
	if (WIFEXITED(status))
		*get_status_code() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
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
	if (*saved_pwd())
		free(*saved_pwd());
	free_all_env(get_env_head());
	free_all();
	exit(nb);
}
