/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghita <ghita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:13 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/14 15:53:18 by ghita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	execute_env(void)
{
	t_envp	**envp;
	t_envp	*current;

	envp = get_env_head();
	current = *envp;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if(*get_error_check())
		*get_status_code() = 0;
}
