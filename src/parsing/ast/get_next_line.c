/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:39:28 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/04 17:13:17 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

char	*ft_strjoin_(char *s1, char *s2)
{
	char			*join;

	unsigned int (i), (j), (size);
	if (!s1 || !s2)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2));
	join = (char *)ft_malloc(sizeof(char) * size + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[size] = '\0';
	free_one(s1);
	return (join);
}

void	fill_in_save(int fd, ssize_t *rd, char **save, char **buff)
{
	while (1)
	{
		*rd = read(fd, *buff, BUFFER_SIZE);
		if (*rd == 0 || *rd == -1)
			break ;
		(*buff)[*rd] = '\0';
		if (!(*save))
			*save = ft_strdup(*buff);
		else
			*save = ft_strjoin_(*save, *buff);
		if (ft_strchr(*save, '\n'))
			break ;
	}
}

char	*read_line(char **save, ssize_t rd)
{
	char	*line;
	char	*new;
	char	*nl_ptr;

	nl_ptr = ft_strchr(*save, '\n');
	if (nl_ptr)
	{
		line = ft_substr(*save, 0, nl_ptr - *save + 1);
		new = ft_strdup(nl_ptr + 1);
		return (free_one(*save), *save = ft_strdup(new), free_one(new), line);
	}
	else if (!rd && save != NULL)
	{
		new = ft_strdup(*save);
		if (!new || !new[0])
			return (free_one(*save), free_one(new), NULL);
		return (free_one(*save), *save = NULL, new);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buff;
	ssize_t		rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_malloc((BUFFER_SIZE * sizeof(char)) + 1);
	if (!buff)
		return (NULL);
	fill_in_save(fd, &rd, &save, &buff);
	free_one(buff);
	if (!save)
		return (NULL);
	return (read_line(&save, rd));
}
