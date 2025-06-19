/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:09 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/19 19:41:05 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include "../../include/heredoc.h"

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

static int	expand_heredoc_file(int fd, t_file *file)
{
	int		heredoc_fd;
	char	*line;
	char	*eof;
	int		to_expand;

	to_expand = !(is_quoted(file->delimiter));
	eof = ft_strjoin(remove_quotes(file->delimiter), "\n");
	heredoc_fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		set_exec_error(HEREDOC_PATH, 1);
	line = get_next_line(fd);
	while (line && ft_strcmp(line, eof))
	{
		if (to_expand)
			line = heredoc_expander(line);
		write(heredoc_fd, line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (restore_heredoc_offset(heredoc_fd));
}

int	open_file(t_file *file)
{
	int	fd;

	if (file->type == APPEND)
		fd = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		fd = open(file->filename, O_RDONLY);
	else
		fd = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		set_exec_error(file->filename, 1);
	if (file->type == HERE_DOC)
		fd = expand_heredoc_file(fd, file);
	return (fd);
}

void	redirect_io(int fd, t_file *file)
{
	if (file->type == APPEND || file->type == OUTPUT_RED)
		dup2(fd, STDOUT_FILENO);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
}

void	open_redirects(t_file *redirect)
{
	t_file	*current;
	int		fd;

	current = redirect;
	while (current)
	{
		fd = open_file(current);
		if (*get_error_check() == true)
		{
			redirect_io(fd, current);
			close(fd);
		}
		current = current->next;
	}
}
