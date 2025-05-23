/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/20 16:07:39 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/expander.h"

char	**expander(char **args)
{
	t_expand	*expand;
	// char **arg;

	if (!args)
		printf("arg list rah khawya asmitk\n");
	expand = init_expand(args);
	while (expand && expand->args && expand->args[expand->i]) // example : { echo; $hi; NULL }
	{
		expand_param(expand); //looks for $ dquoted or unquoted then replace it
		field_split(expand); // split nodes value by IFS (tab or space) outside quotes
		// check wash tal hna mzyan
		expand_pathname(expand); // look for * then replace it with correspond files + split it in parallel and add to (include field split)
		expand->i++;
	}
	print_t_arg(expand->arg);
	// arg = remove_quotes_from_all(expand);
	// return(arg);
	return NULL;
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
	return (exp);
}

void	expand_pathname(t_expand *exp)
{
	char **files;
	t_arg *arg;

	files = get_files();
	replace_unquoted_asterisk(exp);
	arg = exp->arg;
	while (arg)
	{
		match_star(exp, files, arg);
		arg = arg->next;
	}
}

void	match_star(t_expand *exp, char **files, t_arg *arg)
{
	char *wildcard;
	char *tmp;
	int i;
	int j;

	wildcard = arg->value;
	if (wildcard[0] == -3)
		files = remove_hidden_files(files);
	i = 0;
	while (files[i])
	{
		tmp = files[i];
		while (wildcard[j])
		{
			
		}
		
	}
	
}

void	arg_addmid(t_arg **head, t_arg *mid, t_arg *new)
{
	if (!head || !new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	new->next = mid->next;
	mid->next = new;
}

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
	i = 0;
	while ((entry = readdir(dir)) != NULL)
		i++;
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while ((entry = readdir(dir)) != NULL)
		ret[i++] = strdup(entry->d_name);
	ret[i] = NULL;
	closedir(dir);
	return (ret);
}

//TODO : expand_param(t_expand *expand)========================>> DONE
//TODO : expand_inside_double_quote(exp)=======================>> DONE
//TODO : copy_characters_until_quote(exp)======================>> DONE
//TODO : expand_unquoted(exp)==================================>> DONE
//TODO : strnchr !!!!!!!!!!!!!!!!!!!!!!!!======================>> DONE
//TODO : field_split(t_expand *expand)=========================>> DONE
//TODO : expand_path(t_expand *expand)=========================>>
//TODO : remove_quotes_from_all(t_expand *expand)==============>>
//TODO : init_expand ==========================================>>