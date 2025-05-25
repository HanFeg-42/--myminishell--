/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/22 11:39:26 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

char	**expander(char **args)
{
	t_expand	*expand;
	char **arg;

	if (!args)
		printf("arg list rah khawya asmitk\n");
	expand = init_expand(args);
	while (expand && expand->args && expand->args[expand->i]) // example : { echo; $hi; NULL }
	{
		expand_param(expand); //looks for $ dquoted or unquoted then replace it
		field_split(expand); // split nodes value by IFS (tab or space) outside quotes
		expand_pathname(expand); // look for * then replace it with correspond files + split it in parallel and add to (include field split)
		expand->i++;
	}
	print_t_arg(expand->arg);
	arg = remove_quotes_from_all(expand);
	if (!arg)
		printf("diri chi 7araka!\n");
	int j = 0;
	while (arg[j])
	{
		printf("%s --", arg[j]);
		j++;
	}
	printf("\n");
	return(arg);
}


char **remove_quotes_from_all(t_expand *exp)
{
	char **ret;
	int i;
	int j;

	i = 0;
	ret = NULL;
	while (exp->arg)
	{
		if (exp->arg->file)
		{
			j = 0;
			while (exp->arg->file[j])
			{
				ret = ft_realloc(ret, sizeof(char *) * (i + 2));
				if (!ret)
					return (NULL);
				ret[i] = ft_strdup(exp->arg->file[j]);
				i++; j++;
				ret[i] = NULL;
			}
		}
		else
		{
			ret = ft_realloc(ret, sizeof(char *) * (i + 2));
			if (!ret)
				return (NULL);
			ret[i++] = undo_char_changes(remove_quotes(exp->arg->value));
			ret[i] = NULL;
		}
		exp->arg = exp->arg->next;
	}
	return (ret);
}

// int	arg_size(t_arg *arg)
// {
// 	int count;

// 	count = 0;
// 	while (arg)
// 	{
// 		count++;
// 		arg = arg->next;
// 	}
// 	return (count);
// }

char *undo_char_changes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
			str[i] = 39;
		if (str[i] == -2)
			str[i] = 34;
		if (str[i] == -3)
			str[i] = '*';
		i++;
	}
	return (str);
}

t_expand	*init_expand(char **args)
{
	t_expand	*exp;

	exp = ft_malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	exp->arg = NULL;
	exp->args = copy_arr(args);// alloci a zmer
	exp->i = 0;
	exp->stat = 0;
	exp->pos = 0;
	exp->dir_files = get_files();

	return (exp);
}

void	expand_pathname(t_expand *exp)
{
	char **files;
	t_arg *arg;
	int i;
	int size;

	replace_unquoted_asterisk(exp);
	arg = exp->arg;
	while (arg)
	{
		if (ft_strchr(arg->value, -3))
		{
			if (arg->value[0] == -3)
				files = remove_hidden_files(exp->dir_files);
			else
				files = exp->dir_files;
			i = 0;
			size = 0;
			while (files[i])
			{
				if (is_match(files[i], arg->value))
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
		// match_star(exp, files, arg);
		arg = arg->next;
	}
}

int is_match(char *s, char *p)
{
    char *star = NULL;
    char *ss = NULL;

    while (*s) {
        if (*p == *s || *p == -3) {
            if (*p == -3) {
                star = p++;
                ss = s;
            } else {
                p++;
                s++;
            }
        } else if (star) {
            // backtrack: match more characters with -3
            p = star + 1;
            s = ++ss;
        } else {
            return false;
        }
    }

    // skip trailing -3 in pattern
    while (*p == -3) p++;

    return *p == '\0';
}
// *'' $var'' "$USER" '$PWD'
void match_star(t_expand *exp, char **files, t_arg *arg)
{
	char *w;
	char *tmp;
	int i;
	int j;
	int a;
	char *star_pos;
	char *to_find;
	char *file_pos;
	int to_find_size;

	(void)exp;
	a = 0;
	arg->file = NULL;
	w = arg->value;
	if (w[0] == -3 && !w[1])
	{
		arg->file = remove_hidden_files(files);
		return ;
	}
	if (w[0] == -3)
		files = remove_hidden_files(files);
	i = 0;
	while (files[i])
	{
		tmp = files[i];
		// printf("%s\n", tmp);
		j = 0;
		while (w[j])
		{
			if (w[j] != -3)
			{
				star_pos = ft_strchr(w + j, -3);
				if (!star_pos)
				{
					if (!ft_strcmp(w + j, tmp + ft_strlen(tmp) - ft_strlen(w + j)))
					{
						arg->file = ft_realloc(arg->file, sizeof(char *) * (a + 2));
						if (!arg->file)
							return ;
						arg->file[a++] = ft_strdup(files[i]);
						arg->file[a] = NULL;
						break;
					}

					// star_pos = ft_strchr(w + j, '\0');
				}
				to_find = ft_substr(w + j, 0, star_pos - w - j + 1);
				to_find_size = ft_strlen(to_find);
				j += to_find_size;
				file_pos = ft_strnstr(tmp, to_find, to_find_size);//khdmi b strstr
				if (!file_pos)
					break ;
				tmp = file_pos + to_find_size;
			}
			while (w[j] == -3)
				j++;
			if (!(*tmp) && *(w + j))
				break;
			if ((!(*tmp) && !(*(w + j))) || (!(*(w + j)) && *tmp))
			{
				arg->file = ft_realloc(arg->file, sizeof(char *) * (a + 2));
				if (!arg->file)
					return ;
				arg->file[a++] = ft_strdup(files[i]);
				arg->file[a] = NULL;
			}
		}
		i++;
	}
}

char **remove_hidden_files(char **files)
{
	char **ret;
	int i;
	int j;
	int a;

	a = 0;
	i = 0;
	ret = NULL;
	while (files[i])
	{
		if (files[i][0] != '.')
			a++;
		i++;
	}
	ret = ft_malloc(sizeof(char*) * (a + 1));
	if (!ret)
		return (NULL);
	j = 0;
	i = 0;
	while (files[i])
	{
		if (files[i][0] != '.')
		{
			ret[j] = ft_strdup(files[i]);
			j++;
		}
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

// t_arg	*arg_addmid(t_arg **head, t_arg *mid, t_arg *new)
// {
// 	if (!head || !mid || !new)
// 		return (mid);
// 	if (!(*head))
// 	{
// 		*head = new;
// 		return (mid);
// 	}
// 	if (!ft_strchr(mid->value, -3))
// 	{
// 		new->next = mid->next;
// 		if (mid->prev)
// 			mid->prev = new;/// hna lmachakiiiil
// 	}
// 	new->next = mid->next;
// 	if (mid->next)
// 		mid->next = new;
// 	return (mid);
// }

void replace_unquoted_asterisk(t_expand *exp)
{
	int i;
	int stat;
	char *tmp;
	t_arg *curr;

	curr = exp->arg;
	while (curr)
	{
		tmp = curr->value;
		stat = 0;
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == 34 && stat == 0) // inside double quotes
				stat = 1;
			else if ((tmp[i] == 34 && stat == 1) || (tmp[i] == 39 && stat == 2)) // khrjt mn l quoted stat + now on normal stat
				stat = 0;
			else if (tmp[i] == 39 && stat == 0) // inside single quotes
				stat = 2;
			else if (tmp[i] == '*' && stat == 0)
				tmp[i] = -3; // instead of *
			i++;
		}
		curr = curr->next;
	}
}

char **get_files(void)
{
	DIR *dir;
	struct dirent *entry;
	char **ret;
	int i;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir failed");
		return (NULL);
	}
	ret = NULL;
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		ret = ft_realloc(ret, sizeof(char *) * (i + 2));
		if (!ret)
			return (NULL);
		ret[i++] = ft_strdup(entry->d_name);
		ret[i] = NULL;
	}
	closedir(dir);
	return (ret);
}
