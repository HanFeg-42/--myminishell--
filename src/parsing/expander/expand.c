/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 11:55:37 by hfegrach         ###   ########.fr       */
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
		// expand_pathname(expand); // look for * the replace it with correspond files + split it in parallel and add to (include field split)
		// expand_advance(expand); // inncrement i]
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

char	**copy_arr(char **arg)
{
	char	**ret;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
		i++;
	ret = ft_malloc(sizeof(char *) * (i + 1));
	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		ret[i] = ft_strdup(arg[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	print_t_arg(t_arg *arg)
{
	if (!arg)
		return ;
	printf("hello\n");
	while (arg)
	{
		printf("%s -- ", arg->value);
		arg = arg->next;
	}
	printf("\n");
}


//TODO : expand_param(t_expand *expand)========================>> DONE
//TODO : expand_inside_double_quote(exp)=======================>> DONE
//TODO : copy_characters_until_quote(exp)======================>> DONE
//TODO : expand_unquoted(exp)==================================>> DONE
//TODO : strnchr !!!!!!!!!!!!!!!!!!!!!!!!======================>> DONE
//TODO : field_split(t_expand *expand)=========================>> DONE
//TODO : expand_path(t_expand *expand)=========================>>
//TODO : expand_advance(t_expand *expand)======================>>
//TODO : remove_quotes_from_all(t_expand *expand)==============>>
//TODO : init_expand ==========================================>>