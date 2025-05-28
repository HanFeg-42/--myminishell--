/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:42:10 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/27 20:42:00 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*init_token(char *value, t_token_type type)
{
	t_token	*tok;

	tok = ft_malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

t_token	*tokenizer(char *line)
{
	t_lexer	*lexer;
	t_token	*token;
	t_token	*tok_head;

	lexer = init_lexer(line);
	tok_head = NULL;
	token = NULL;
	token = lexer_next_token(lexer);
	while (token)
	{
		token_addback(&tok_head, token);
		token = lexer_next_token(lexer);
	}
	return (tok_head);
}

void	token_addback(t_token **tok_head, t_token *token)
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

t_token	*token_last(t_token *tok_head)
{
	t_token	*current;

	if (!tok_head)
		return (NULL);
	current = tok_head;
	while (current->next)
		current = current->next;
	return (current);
}

void	token_print(t_token *tok)
{
	if (!tok)
		printf("no token");
	while (tok)
	{
		printf("%s \t-- its type : %d | ", tok->value, tok->type);
		tok = tok->next;
	}
}

// void token_free_list(t_token *tok)
// {
//     t_token *next;

//     while (tok)
//     {
//         next = tok->next;
//         if (tok->value && tok->type != EXPANSION)
//             free(tok->value);
//         if (tok)
//             free(tok);
//         tok = next;
//     }
// }