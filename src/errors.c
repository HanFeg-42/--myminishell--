/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 16:22:00 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"
#include "../include/exec.h"

void	*syntax_error(char *err)
{
	*(get_parser_check()) = false;
	*get_status_code() = 2;
	if (err)
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (NULL);
}

void	heredoc_error(char *nb_line, char *lim)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}
