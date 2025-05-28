/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:33:55 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 11:09:04 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

void	ast_print(t_ast *ast)
{
	if (!ast)
		return ;
	expand(ast);
	if (!(*get_parser_check()))
		return ;
	print_args(ast->args);
	print_redirect(ast->redirect);
	ast_print(ast->first_child);
	ast_print(ast->next_sibling);
}

void	print_args(char **args)
{
	int	i;

	if (!args)
		return ;
	printf("args:");
	i = 0;
	while (args[i])
	{
		printf("%s; ", args[i]);
		i++;
	}
	printf("\n");
}

void	print_redirect(t_file *redirect)
{
	t_file	*tmp;

	if (!redirect)
		return ;
	tmp = redirect;
	printf("files:");
	while (redirect)
	{
		printf("%s; ", redirect->filename);
		redirect = redirect->next;
	}
	redirect = tmp;
	printf("\n");
}
