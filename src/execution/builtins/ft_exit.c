/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:16 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/18 22:52:41 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

// void isvalit(char *c)
// {
// 	int longmax;
	
// 	if (*c == '-')
// 	{
// 		longmax = ft_strlen("-9223372036854775808");
// 		if (longmax < ft_strlen(*c))
// 			return 0;
// 		if (longmax == ft_strlen(*c))
// 			return (ft_strcmp("-9223372036854775808", ft_strlen(*c)) > 0);
// 	}
// 	else if (*c == '+')
// 	{
// 		if (ft_strlen("+9223372036854775807") < ft_strlen(*c))
// 			return 0;
// 		if (ft_strlen("+9223372036854775807") == ft_strlen(*c))
// 			return (ft_strcmp("+9223372036854775807", ft_strlen(*c)) > 0);
// 	}
// 	else
// 	{
// 		if (ft_strlen("9223372036854775807") < ft_strlen(*c))
// 			return 0;
// 		if (ft_strlen("9223372036854775807") == ft_strlen(*c))
// 			return (ft_strcmp("9223372036854775807", ft_strlen(*c)) > 0);
// 	}
// }

int	is_numeric(const char *a)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (a[i] == '-' || a[i] == '+')
	{
		if (a[i] == '-')
			sign *= -1;
		i++;
	}
	if (!(a[i] >= '0' && a[i] <= '9'))
		return (false);
	while (a[i] >= '0' && a[i] <= '9')
	{
		res = res * 10 + a[i] - '0';
		if (res > INT_MAX || res * sign < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

void	execute_exit(char **av)
{
	if (*get_num_cmds() <= 1)
		ft_putendl_fd(av[0], 1);
	if (!av[1])
		clean_and_exit(*get_status_code());
	if (!is_numeric(av[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_and_exit(2);
	}
	if (av[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		*get_status_code() = 1;
	}
	else
		clean_and_exit((unsigned char)ft_atoi(av[1]));
}
