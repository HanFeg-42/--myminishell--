/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghita <ghita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:40 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/14 15:53:08 by ghita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int	skip_option(char **arg, int *i)
{
	int	check;
	int	j;

	check = *i;
	while (arg[*i] && arg[*i][0] == '-')
	{
		j = 1;
		while (arg[*i][j] && arg[*i][j] == 'n')
			j++;
		if (arg[*i][j] == '\0')
		{
			if (arg[*i][j - 1] != 'n')
				return (false);
		}
		else
			return (false);
		(*i)++;
	}
	return (!(check == *i));
}

void	execute_echo(char **arg)
{
	int	i;
	int	option;

	i = 1;
	option = skip_option(arg, &i);
	while (arg[i])
	{
		ft_putstr_fd(arg[i++], STDOUT_FILENO);
		if (arg[i])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	if(*get_error_check())
		*get_status_code() = 0;
}


