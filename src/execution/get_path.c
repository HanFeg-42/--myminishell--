/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:06 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/03 16:54:28 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	if (!cmd[0] || (cmd[0] == '.' && ft_strlen(cmd) == 1))
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!strcmp("/bin", cmd))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_path(paths, cmd));
}

char	*concat_path(char *path, char *cmd)
{
	char	*fullpath;
	char	*tmp;

	if (!path || !cmd)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	fullpath = ft_strjoin(tmp, cmd);
	return (fullpath);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*fullpath;

	i = 0;
	while (paths[i])
	{
		fullpath = concat_path(paths[i], cmd);
		if (fullpath && access(fullpath, X_OK) == 0)
		{
			return (fullpath);
		}
		i++;
	}
	return (NULL);
}
