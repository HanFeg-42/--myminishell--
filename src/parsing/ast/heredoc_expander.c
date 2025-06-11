/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:49:58 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/11 20:58:59 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"

char	*heredoc_expander(char *s)
{
	char	*ret;
	char	*dollar_pos;

	if (!s)
		return (NULL);
	ret = ft_strdup("");
	while (*s)
	{
		dollar_pos = ft_strchr(s, '$');
		if (!dollar_pos)
		{
			ret = ft_strjoin(ret, s);
			break ;
		}
		ret = ft_strjoin(ret,
				ft_substr(s, 0, dollar_pos - s));
		ret = ft_strjoin(ret, get_env_name(dollar_pos));
		s = skip_env_var(dollar_pos + 1);
	}
	return (ret);
}

char	*get_env_name(char *s)
{
	char	*var;
	int		i;

	i = 1;
	if (s[i] == '?')
		return (ft_itoa(*get_status_code()));
	while (s[i] && (ft_isalpha(s[1]) || s[1] == '_')
		&& (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	if (i == 1)
		return (ft_strdup("$"));
	var = ft_substr(s, 1, i - 1);
	var = ft_getenv(var);
	var = replace_quotes(var);
	return (var);
}

char	*replace_quotes(char *var)
{
	char	*ret;
	int		i;

	if (!var)
		return (NULL);
	ret = gc_alloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (var[i])
	{
		if (var[i] == 39)
			ret[i] = -1;
		else if (var[i] == 34)
			ret[i] = -2;
		else
			ret[i] = var[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*skip_env_var(char *s)
{
	if (*s == '?')
	{
		s++;
		return (s);
	}
	while (*s && ft_isalpha(s[0]) && (*s == '_' || ft_isalnum(*s)))
		s++;
	return (s);
}

char	*ft_getenv(char *var)
{
	t_envp	*current;

	current = *get_env_head();
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
