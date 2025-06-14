/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 17:59:08 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"

int	is_empty_cmd(t_ast *simple_cmd)
{
	return (!simple_cmd->args && !simple_cmd->redirect);
}

int	check_and_or_token(t_token *token)
{
	if (!token)
		return (-1);
	if (token->type == AND)
		return (AST_AND);
	else if (token->type == OR)
		return (AST_OR);
	return (-1);
}

static void	copy_ptr(char **ptr, char **new_ptr, int size)
{
	int	i;

	i = 0;
	while (ptr[i] && i < size - 1)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		i++;
	}
	new_ptr[i] = NULL;
}

static void	free_old_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free_one(ptr[i]);
		i++;
	}
	free_one(ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	**new_ptr;

	if (!ptr)
		return (gc_alloc(size));
	new_ptr = gc_alloc(size);
	copy_ptr(ptr, new_ptr, size);
	free_old_ptr(ptr);
	return (new_ptr);
}
