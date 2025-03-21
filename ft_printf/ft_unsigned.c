/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:21:18 by hfegrach          #+#    #+#             */
/*   Updated: 2024/11/20 12:13:48 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n > 9)
		ret += ft_unsigned(n / 10);
	ret += ft_character(n % 10 + '0');
	return (ret);
}
