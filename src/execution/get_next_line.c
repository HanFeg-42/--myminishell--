/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:39:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 21:55:14 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	res = gc_alloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

static void	store_line(char **temp, char **line, char *newline_pos)
{
	if (newline_pos)
	{
		*line = ft_substr(*temp, 0, newline_pos - *temp + 1);
		*temp = ft_strdup(newline_pos + 1);
		if (!**temp)
			*temp = NULL;
	}
	else
	{
		*line = ft_strdup(*temp);
		*temp = NULL;
	}
}

static char	*read_and_store(int fd, char *temp)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = gc_alloc((size_t)BUFFER_SIZE + 1);
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
	if (bytes_read < 0)
		return (NULL);
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
