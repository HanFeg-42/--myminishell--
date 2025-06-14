/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghita <ghita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:18 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/14 15:53:28 by ghita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	execute_export(char **args)
{
	t_envp	**envp;
	int		i;

	envp = get_env_head();
	i = 0;
	if (!args[i])
	{
		print_sorted_env(envp);
		return ;
	}
	while (args[i])
	{
		handle_single_export(args[i], envp);
		i++;
	}
	if(*get_error_check())
		*get_status_code() = 0;
}

void	update_export(t_envp **envp, char *key, char *value)
{
	t_envp	*node;

	node = find_node(key);
	if (!node)
		env_add(envp, env_create(key, value));
	else
	{
		if (node->value)
			free(node->value);
		node->value = ft_str_dup(value);
	}
}

void	handle_single_export(char *arg, t_envp **envp)
{
	char	*key;
	char	*value;
	char	*pos;

	pos = ft_strchr(arg, '=');
	if (pos == arg || !is_key_valid(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		set_exec_error (NULL, 1);
		return ;
	}
	if (pos)
	{
		key = ft_substr(arg, 0, pos - arg);
		value = ft_strdup(pos + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	update_export(envp, key, value);
}

void	print_sorted_env(t_envp **envp)
{
	t_envp	**copy;
	t_envp	*current;

	copy = copy_env(envp);
	if (!*get_error_check())
		return ;
	sort_envp(copy);
	current = *copy;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
	free_all_env(copy);
	free(copy);
}
