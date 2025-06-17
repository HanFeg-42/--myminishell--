/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:39:14 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/17 14:39:15 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sub_str(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	if (src_len - start < len)
		len = src_len - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
