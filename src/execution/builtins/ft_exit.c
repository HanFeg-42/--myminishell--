/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:16 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 11:23:32 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	is_numeric(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (false);
		i++;
	}
	return (true);
}

void	execute_exit(char **av)
{
	ft_putendl_fd(av[0], 1);
	if (!av[1])
		clean_and_exit(NULL, *get_status_code());
	if (!is_numeric(av[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_and_exit(NULL, 2);
	}
	if (av[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		*get_status_code() = 1;
	}
	else
		clean_and_exit(NULL, (unsigned char)ft_atoi(av[1]));
}
