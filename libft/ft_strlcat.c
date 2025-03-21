/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:23:33 by hfegrach          #+#    #+#             */
/*   Updated: 2024/11/09 15:41:14 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstsize;
	size_t	srcsize;

	srcsize = ft_strlen(src);
	if (!dst && size == 0)
		return (srcsize);
	dstsize = ft_strlen(dst);
	if (size <= dstsize)
		return (size + srcsize);
	i = 0;
	while (i < size - dstsize - 1 && src[i])
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	dst[dstsize + i] = '\0';
	return (dstsize + srcsize);
}
