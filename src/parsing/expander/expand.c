/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:52:23 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/16 17:17:09 by hfegrach         ###   ########.fr       */
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
		expand_pathname(expand); // look for * the replace it with correspond files + split it in parallel and add to (include field split)
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
	(void)exp;
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