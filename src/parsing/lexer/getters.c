/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:41:56 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/27 20:42:43 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
