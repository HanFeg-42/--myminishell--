/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:31:52 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/19 18:32:09 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	*ft_strdup_(const char *str)
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

char	*ft_substr_(char const *s, unsigned int start, size_t len)
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

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}
