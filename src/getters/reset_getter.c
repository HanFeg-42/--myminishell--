/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:22 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/19 18:26:56 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include "../../include/minishell.h"

void	reset_checker_state(void)
{
	*get_error_check() = true;
	*get_parser_check() = true;
	*get_heredoc_check() = true;
}
