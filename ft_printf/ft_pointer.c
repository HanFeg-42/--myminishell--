/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:13:14 by hfegrach          #+#    #+#             */
/*   Updated: 2024/11/19 16:40:44 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexa(unsigned long n)
{
	int	re;

	re = 0;
	if (n > 15)
		re += ft_hexa(n / 16);
	re += (write(1, &"0123456789abcdef"[n % 16], 1));
	return (re);
}

int	ft_pointer(unsigned long l)
{
	int	ret;

	ret = 0;
	ret += ft_string("0x");
	ret += ft_hexa(l);
	return (ret);
}
