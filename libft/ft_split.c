/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:22:18 by marvin            #+#    #+#             */
/*   Updated: 2025/06/01 20:56:52 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	j = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			j = 1;
		else if (s[i] != c && j == 1)
		{
			count++;
			j = 0;
		}
		i++;
	}
	return (count);
}

static char	**ft_freeme(char **s, int index)
{
	while (index >= 0)
	{
		free(s[index]);
		index--;
	}
	free(s);
	return (NULL);
}

static char	**ft_slices(char **ret, char const *s, char c, int a)
{
	int	len;
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			j = 1;
		else if (s[i] != c && j == 1)
		{
			len = 0;
			while (s[i + len] && s[i + len] != c)
				len++;
			ret[a] = ft_substr(s, i, len);
			if (!ret[a])
				return (ft_freeme(ret, a));
			a++;
			j = 0;
		}
		i++;
	}
	ret[a] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		a;

	a = 0;
	if (!s)
		return (NULL);
	ret = ft_malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!ret)
		return (NULL);
	ret = ft_slices(ret, s, c, a);
	return (ret);
}
