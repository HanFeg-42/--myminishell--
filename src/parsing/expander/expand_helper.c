/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:51:20 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 16:51:21 by hfegrach         ###   ########.fr       */
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
	if (!arg)
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
