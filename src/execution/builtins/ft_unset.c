/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:23 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/02 16:00:24 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	execute_unset(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free_env(args[i]);
		i++;
	}
}

void	free_env(void *key)
{
	t_envp	**envp;
	t_envp	*curr;
	t_envp	*prev;

	envp = get_env_head();
	if (!envp || !*envp)
		return ;
	curr = *envp;
	prev = NULL;
	if (!ft_strcmp(curr->key, key))
	{
		*envp = (*envp)->next;
		free(curr);
		return ;
	}
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			prev->next = curr->next;
			return (free(curr));
		}
		prev = curr;
		curr = curr->next;
	}
}
