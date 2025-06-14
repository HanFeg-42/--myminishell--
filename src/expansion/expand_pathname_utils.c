/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 15:49:38 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	sort_strings(char **arr)
{
	size_t	i;
	char	*tmp;
	int		sorted;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i + 1])
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

char	**get_cwd_files(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**ret;
	size_t			i;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir failed");
		return (NULL);
	}
	ret = NULL;
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		append_to_array(&ret, &i, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(ret);
	return (ret);
}

static char	**get_root_dirs(void)
{
	struct dirent	*entry;
	char			**ret;
	DIR				*dir;
	size_t			i;

	dir = opendir("/");
	if (!dir)
	{
		perror("opendir failed");
		return (NULL);
	}
	ret = NULL;
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		append_to_array(&ret, &i, ft_strjoin("/", entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(ret);
	return (ret);
}

static char	**get_dirs(char	**files)
{
	char			**ret;
	size_t			i;
	int				j;

	ret = NULL;
	i = 0;
	j = 0;
	while (files[j])
	{
		if (is_directory(files[j]))
			append_to_array(&ret, &i, ft_strjoin(files[j], "/"));
		j++;
	}
	sort_strings(ret);
	return (remove_hidden_files(ret));
}

char	**get_files(t_expand *exp, t_arg *arg)
{
	if (arg->value[0] == STAR && !ft_strchr(arg->value, '/'))
		return (remove_hidden_files(exp->cwd_files));
	else if (arg->value[0] == '/')
		return (remove_hidden_files(get_root_dirs()));
	else if (*(arg->value + ft_strlen(arg->value) - 1) == '/')
		return (get_dirs(exp->cwd_files));
	else
		return (exp->cwd_files);
	return (NULL);
}
