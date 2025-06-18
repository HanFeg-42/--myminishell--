/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:41:56 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/18 23:37:17 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"

int	*get_parser_check(void)
{
	static int	check = true;

	return (&check);
}

int	*get_heredoc_check(void)
{
	static int	check = true;

	return (&check);
}

size_t	*get_arg_size(void)
{
	static size_t	size = 0;

	return (&size);
}

int	*get_status_code(void)
{
	static int	status = 0;

	return (&status);
}

int	*get_num_cmds(void)
{
	static int	nbr = 0;

	return (&nbr);
}

