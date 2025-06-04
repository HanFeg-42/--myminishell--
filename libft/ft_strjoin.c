/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:19:47 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 21:41:58 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;

	unsigned int (i), (j), (size_s1), (size_s2);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	join = (char *)ft_malloc(sizeof(char) * size_s1 + size_s2 + 1);
	i = 0;
	while (i < size_s1)
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size_s2)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[size_s1 + size_s2] = '\0';
	return (join);
}
