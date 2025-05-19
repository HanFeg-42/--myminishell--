/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:15:40 by marvin            #+#    #+#             */
/*   Updated: 2024/11/09 13:47:00 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	nbr_size(long n, long d)
{
	unsigned int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

static	char	*full_s(char *s, long d, long n, int i)
{
	while (n >= 0 && d > 0)
	{
		s[i++] = n / d + '0';
		n = n % d;
		d /= 10;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int nbr)
{
	int		i;
	long	n;
	long	d;
	char	*s;

	i = 0;
	n = nbr;
	d = 1;
	s = ft_malloc(sizeof(char) * (nbr_size(n, d) + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[i] = '-';
		i++;
		n = -n;
	}
	while (d * 10 <= n)
		d *= 10;
	s = full_s(s, d, n, i);
	return (s);
}
