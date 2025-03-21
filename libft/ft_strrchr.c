/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:26:35 by marvin            #+#    #+#             */
/*   Updated: 2024/11/07 10:08:56 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	tmp;
	int	a;

	tmp = 0;
	a = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			tmp = i;
			a++;
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str + i);
	if (!tmp && !a)
		return (NULL);
	return ((char *)str + tmp);
}
