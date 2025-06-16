/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:13 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/16 15:59:51 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	execute_env(char **args)
{
	t_envp	**envp;
	t_envp	*current;

	if (*args)
		return (set_error("env : too many agruments\n"));
	envp = get_env_head();
	current = *envp;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if (*get_error_check())
		*get_status_code() = 0;
}
