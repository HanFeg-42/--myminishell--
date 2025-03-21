/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:49 by marvin            #+#    #+#             */
/*   Updated: 2024/11/10 16:05:31 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ret;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;
	size_t			len;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1);
	while (i > start && ft_strchr(set, s1[i]))
		i--;
	end = i;
	len = end - start + 1;
	ret = ft_substr(s1, start, len);
	return (ret);
}
