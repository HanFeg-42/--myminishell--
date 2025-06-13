/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:42 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/11 22:39:42 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

t_envp	*env_create(char *key, char *value)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->key = ft_str_dup(key);
	if (value)
		new->value = ft_str_dup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	env_add(t_envp **envp, t_envp *new)
{
	if (!envp || !new)
		return ;
	if (!(*envp))
	{
		*envp = new;
		return ;
	}
	(get_env_last(*envp))->next = new;
}

t_envp	*get_env_last(t_envp *env)
{
	t_envp	*current;

	current = env;
	while (current && current->next)
		current = current->next;
	return (current);
}

char	**convert_envp(void)
{
	char	**envp;
	t_envp	**old_envp;
	int		size;
	t_envp	*current;
	char	*holder;

	old_envp = get_env_head();
	size = envp_size(old_envp);
	envp = gc_alloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	current = *old_envp;
	size = 0;
	while (current)
	{
		holder = ft_strjoin(current->key, "=");
		holder = ft_strjoin(holder, current->value);
		envp[size] = ft_strdup(holder);
		size++;
		current = current->next;
	}
	envp[size] = NULL;
	return (envp);
}

int	envp_size(t_envp **old_envp)
{
	int		size;
	t_envp	*current;

	size = 0;
	current = *old_envp;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
// void	print_env(t_envp **env)
// {
// 	t_envp *current;

// 	current = *env;
// 	while (current)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// }
