/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:10 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/12 17:51:54 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = gc_alloc(sizeof(t_lexer));
	lexer->line = ft_strdup(line);
	lexer->i = 0;
	lexer->c = line[0];
	lexer->line_size = ft_strlen(line);
	return (lexer);
}

static t_token	*token_last(t_token *tok_head)
{
	t_token	*current;

	if (!tok_head)
		return (NULL);
	current = tok_head;
	while (current->next)
		current = current->next;
	return (current);
}

static void	token_addback(t_token **tok_head, t_token *token)
{
	t_token	*last;

	if (!tok_head || !token)
		return ;
	if (!(*tok_head))
	{
		*tok_head = token;
		return ;
	}
	last = token_last(*tok_head);
	last->next = token;
	token->prev = last;
}

t_token	*tokenizer(char *line)
{
	t_lexer	*lexer;
	t_token	*token;
	t_token	*tok_head;

	lexer = init_lexer(line);
	tok_head = NULL;
	token = lexer_next_token(lexer);
	while (token)
	{
		token_addback(&tok_head, token);
		token = lexer_next_token(lexer);
	}
	return (tok_head);
}
