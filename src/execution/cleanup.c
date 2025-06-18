/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:30:37 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/18 17:39:52 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

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
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
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

void	clean_and_exit(int nb)
{
	if (*saved_pwd())
		free(*saved_pwd());
	free_all_env(get_env_head());
	free_all();
	exit(nb);
}

void	close_pipe(int *pipefd)
{
	if (!pipefd)
		return ;
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}
