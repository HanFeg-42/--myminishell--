/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:39:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 18:32:18 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	store_line(char **temp, char **line, char *newline_pos)
{
	char	*old_temp;

	if (newline_pos)
	{
		*line = ft_substr_(*temp, 0, newline_pos - *temp + 1);
		old_temp = *temp;
		*temp = ft_strdup_(newline_pos + 1);
		free(old_temp);
		if (!**temp)
		{
			free(*temp);
			*temp = NULL;
		}
	}
	else
	{
		*line = ft_strdup_(*temp);
		free(*temp);
		*temp = NULL;
	}
}

static char	*read_and_store(int fd, char *temp)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		temp = ft_strjoin_(temp, buf);
		if (ft_strchr(temp, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bytes_read < 0)
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	char		*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = read_and_store(fd, temp);
	if (!temp)
		return (NULL);
	newline_pos = ft_strchr(temp, '\n');
	store_line(&temp, &line, newline_pos);
	return (line);
}
