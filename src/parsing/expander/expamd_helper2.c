/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expamd_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:51:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 11:39:31 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

char	**copy_arr(char **arg)
{
	char	**ret;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
		i++;
	ret = ft_malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		ret[i] = ft_strdup(arg[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	print_t_arg(t_arg *arg)
{
	if (!arg)
		return ;
	printf("hello\n");
	while (arg)
	{
		printf("%s -- ", arg->value);
		arg = arg->next;
	}
	printf("\n");
}

//======================from FIELD SPLIT==========================

void	arg_add(t_arg **head, t_arg *new)
{
	t_arg	*last;

	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_arg	*arg_create(char *value)
{
	t_arg	*new;

	if (!value)
		return (NULL);
	new = ft_malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = value;
	new->file = NULL;
	new->next = NULL;
	return (new);
}
