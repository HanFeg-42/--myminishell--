/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:43:12 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/17 14:43:13 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_dup(const char *str)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = ft_strlen(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
