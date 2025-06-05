/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/05 08:13:29 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"
#include <dirent.h>

void	expand_pathname(t_expand *exp)
{
	t_arg	*arg;

	replace_unquoted_asterisk(exp);
	arg = exp->arg;
	while (arg)
	{
		if (ft_strchr(arg->value, -3)
			&& (arg->prev == NULL
				|| (arg->prev != NULL
				&& arg->prev->value != NULL
				&& ft_strcmp("export", arg->prev->value))))
			arg_traversal(exp, arg);
		arg = arg->next;
	}
}

void	arg_traversal(t_expand *exp, t_arg *arg)
{
	int		i;
	int		size;
	char	**files;

	if (arg->value[0] == -3)
		files = remove_hidden_files(exp->dir_files);
	else if (arg->value[0] == '/')
		files = get_root_dirs();
	else if (*(arg->value + ft_strlen(arg->value) - 1) == '/')
		files = get_dirs();
	else
		files = exp->dir_files;
	if (!files)
		return ;
	i = 0;
	size = 0;
	while (files[i])
	{
		if (is_match(files[i], remove_quotes(arg->value)))
		{
			arg->file = ft_realloc(arg->file, sizeof(char *) * (size + 2));
			arg->file[size++] = ft_strdup(files[i]);
			arg->file[size] = NULL;
		}
		i++;
	}
}

int	is_match(char *filename, char *pattern)
{
	char	*asterisk;
	char	*track_pos;

	asterisk = NULL;
	track_pos = NULL;
	while (*filename)
	{
		if (*pattern == *filename || *pattern == -3)
			track_positions(&asterisk, &track_pos, &filename, &pattern);
		else if (asterisk)
		{
			pattern = asterisk + 1;
			filename = ++track_pos;
		}
		else
			return (0);
	}
	while (*pattern == -3)
		pattern++;
	return (*pattern == '\0');
}

void	track_positions(char **star, char **p_pos, char **s, char **p)
{
	if (*(*p) == -3)
	{
		(*star) = (*p)++;
		(*p_pos) = *s;
	}
	else
	{
		(*p)++;
		(*s)++;
	}
}

void sort_strings(char **arr)
{
    int i;
    char *tmp;
    int sorted;

	sorted = 0;
    while (!sorted) {
        sorted = 1;
        i = 0;
        while (arr[i + 1]) {
            if (ft_strcmp(arr[i], arr[i + 1]) > 0) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                sorted = 0;
            }
            i++;
        }
    }
}

char	**get_files(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**ret;
	int				i;

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
		ret = ft_realloc(ret, sizeof(char *) * (i + 2));
		ret[i++] = ft_strdup(entry->d_name);
		ret[i] = NULL;
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(ret);
	return (ret);
}

char	**get_root_dirs(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**ret;
	int				i;

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
		ret = ft_realloc(ret, sizeof(char *) * (i + 2));
		ret[i++] = ft_strjoin("/", entry->d_name);
		ret[i] = NULL;
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(ret);
	return (remove_hidden_files(ret));
}

int	is_directory(char *pathname)
{
	struct stat	statbuf;

	stat(pathname, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

char	**get_dirs(void)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**ret;
	int				i;

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
		ret = ft_realloc(ret, sizeof(char *) * (i + 2));
		if (is_directory(entry->d_name))
		{
			ret[i++] = ft_strjoin(entry->d_name, "/");
			printf("dirr\n");
			ret[i] = NULL;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	sort_strings(ret);
	if (!ret)
		printf("khawia\n");
	return (ret);
}
