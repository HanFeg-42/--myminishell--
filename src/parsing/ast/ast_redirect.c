/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:28:27 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 23:06:27 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"

void	io_redirect(t_token **token, t_ast *simple_cmd)
{
	if (!(*token))
		return ;
	if ((*token)->next && (*token)->next->type == WORD)
	{
		if ((*token)->type != HERE_DOC)
		{
			redirect_add(&simple_cmd->redirect,
				redirect_create((*token)->type, (*token)->next->value, NULL));
		}
		else
			heredoc_handler((*token)->next->value, &simple_cmd->redirect);
		token_advance(token);
		token_advance(token);
	}
	else
	{
		token_advance(token);
		syntax_error(NULL);
	}
}

void	redirect_list(t_token **token, t_ast *subshell)
{
	while (is_token_redirect(*token))
		io_redirect(token, subshell);
}

t_file	*redirect_create(int type, char *filename, char *delim)

{
	t_file	*redirect_file;

	redirect_file = gc_alloc(sizeof(t_file));
	if (!redirect_file)
		return (NULL);
	redirect_file->filename = ft_strdup(filename);
	if (delim != NULL)
		redirect_file->delimiter = ft_strdup(delim);
	else
		redirect_file->delimiter = NULL;
	redirect_file->expanded = NULL;
	redirect_file->type = type;
	redirect_file->next = NULL;
	return (redirect_file);
}

void	redirect_add(t_file **redirect, t_file *new)
{
	t_file	*current;

	if (!redirect || !new)
		return ;
	if (!(*redirect))
		*redirect = new;
	else
	{
		current = (*redirect);
		while (current->next)
			current = current ->next;
		current->next = new;
	}
}

int	is_token_redirect(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == INPUT_RED
		|| token->type == OUTPUT_RED
		|| token->type == APPEND
		|| token->type == HERE_DOC)
		return (1);
	return (0);
}
