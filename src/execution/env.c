/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:44 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 15:19:26 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

t_envp	**get_env_head(void)
{
	static t_envp	*head;

	return (&head);
}

char	**saved_pwd(void)
{
	static char	*pwd;

	return (&pwd);
}

void	get_basics(void)
{
	char	**basics;

	*saved_pwd() = getcwd(NULL, 0);
	basics = ft_malloc(sizeof(char *) * 5);
	if (!basics)
	{
		set_exec_error("malloc", 1);
		return ;
	}
	basics[0] = ft_strjoin("PWD=", *saved_pwd());
	basics[2] = ft_strdup("PATH=/app/bin:/usr/bin:/bin");
	basics[1] = ft_strdup("SHLVL=1");
	basics[3] = ft_strdup("_=./minishell");
	basics[4] = NULL;
	execute_export(basics);
	return ;
}

void	free_key_value(char *key, char *value)
{
	if (key)
		free (key);
	if (value)
		free (value);
}

void	get_new_env(t_envp **new_envp, char **old_env)
{
	int		i;
	char	*equal_pos;
	char	*key;
	char	*value;

	i = 0;
	while (old_env[i])
	{
		equal_pos = ft_strchr(old_env[i], '=');
		if (!equal_pos)
		{
			key = ft_str_dup(old_env[i]);
			value = NULL;
		}
		else
		{
			key = ft_sub_str(old_env[i], 0, equal_pos - old_env[i]);
			value = ft_str_dup(equal_pos + 1);
		}
		env_add(new_envp, env_create(key, value));
		i++;
		free_key_value(key, value);
	}
	get_basics();
	return ;
}
