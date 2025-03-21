/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:14:21 by hfegrach          #+#    #+#             */
/*   Updated: 2024/11/20 12:02:26 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_subprint(char c, va_list ap)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret = ft_character(va_arg(ap, int));
	else if (c == 's')
		ret = ft_string(va_arg(ap, char *));
	else if (c == 'p')
		ret = ft_pointer(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		ret = ft_decint(va_arg(ap, int));
	else if (c == 'u')
		ret = ft_unsigned(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		ret = ft_hexadecimal(va_arg(ap, unsigned int), c);
	else if (c == '%' || c)
		ret = ft_character(c);
	return (ret);
}
