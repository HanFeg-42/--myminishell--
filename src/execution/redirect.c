/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:09 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/15 16:50:21 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	num_of_redirects(t_file *lst)
{
	int		len;
	t_file	*current;

	if (!lst)
		return (0);
	current = lst;
	len = 0;
	while (current)
	{
		current = current->next;
		len++;
	}
	return (len);
}

int	open_file(t_file *file)
{
	int fd;
	
	if (file->type == APPEND)
		fd = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		fd = open(file->filename, O_RDONLY);
	else
		fd = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		set_exec_error(file->filename, 1);
	return (fd);
}

void	redirect_io(int fd, t_file *file)
{
	if (file->type == APPEND || file->type == OUTPUT_RED)
		dup2(fd, STDOUT_FILENO);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
}

void open_redirects(t_file *redirect)
{
	t_file	*current;
	int		fd;

	current = redirect;
	while (current)
	{
		fd= open_file(current);
		if ((*get_error_check()))
		{
			redirect_io(fd, current);
			close(fd);
		}
		current = current->next;
	}
}



