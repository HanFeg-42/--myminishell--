/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:54:15 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 23:21:10 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/exec.h"

int	is_ifs(int c)
{
	return (c == ' ' || c == '\t');
}

int	is_quoted(char *eof)
{
	return (ft_strchr(eof, '"') || ft_strchr(eof, '\''));
}

int	is_directory(char *pathname)
{
	struct stat	statbuf;

	if (!stat(pathname, &statbuf))
		return (S_ISDIR(statbuf.st_mode));
	return (false);
}
