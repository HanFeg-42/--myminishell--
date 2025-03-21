/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:24:22 by hfegrach          #+#    #+#             */
/*   Updated: 2024/11/20 12:18:54 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		ret;
	va_list	ap;

	if (!s || write(1, 0, 0) == -1)
		return (-1);
	va_start(ap, s);
	ret = 0;
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			ret += ft_subprint(*(++s), ap);
		}
		else if (*s != '%')
		{
			ret += ft_character(*s);
		}
		s++;
	}
	va_end(ap);
	return (ret);
}
