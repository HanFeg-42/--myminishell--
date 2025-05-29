/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 11:42:32 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

void	expand_pathname(t_expand *exp)
{
	t_arg	*arg;

	replace_unquoted_asterisk(exp);
	arg = exp->arg;
	while (arg)
	{
		if (ft_strchr(arg->value, -3))
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
			if (!arg->file)
				return ;
			arg->file[size++] = ft_strdup(files[i]);
			arg->file[size] = NULL;
		}
		i++;
	}
}

// int is_match(char *s, char *p)
// {
//     char *asterisk = NULL;
//     char *track_pos = NULL;

//     while (*s)
//     {
//         if (*p == *s || *p == -3)
//         {
//             if (*p == -3)
//                 (asterisk = p++, track_pos = s);
//             else
//                 (p++, s++);
//         }
//         else if (asterisk)
//         {
//             p = asterisk + 1;
//             s = ++track_pos;
//         }
//         else
//             return (0);
//     }
//     while (*p == -3)
//         p++;
//     return (*p == '\0');
// }

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
		if (!ret)
			return (NULL);
		ret[i++] = ft_strdup(entry->d_name);
		ret[i] = NULL;
		entry = readdir(dir);
	}
	closedir(dir);
	return (ret);
}
