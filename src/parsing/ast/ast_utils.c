/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:03:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 23:34:20 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"
#include "../../../include/heredoc.h"

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

void	arg_size(t_token *token)
{
	*get_arg_size() = 0;
	while (token)
	{
		if (token->type == PIPE
			|| token->type == AND
			|| token->type == OR
			|| token->type == OPAREN
			|| token->type == CPAREN)
			break ;
		*get_arg_size() = *get_arg_size() + 1;
		token = token->next;
	}
}

int	restore_heredoc_offset(int heredoc_fd, char *path)
{
	close(heredoc_fd);
	heredoc_fd = open(path, O_RDONLY);
	if (heredoc_fd < 0)
		set_exec_error(path, 1);
	return (heredoc_fd);
}
