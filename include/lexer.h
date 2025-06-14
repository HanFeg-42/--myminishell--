/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:16 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 17:45:03 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	ID,
	WORD,
	AND,
	OR,
	PIPE,
	INPUT_RED,
	OUTPUT_RED,
	APPEND,
	HERE_DOC,
	OPAREN,
	CPAREN,
	EOI
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_lexer
{
	char			*line;
	char			c;
	int				i;
	int				line_size;
}					t_lexer;

void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespaces(t_lexer *lexer);
t_token			*lexer_get_word(t_lexer *lexer);
t_token			*lexer_advance_current(t_lexer *lexer, t_token_type type);
t_token			*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token			*lexer_advance_with2(t_lexer *lexer, t_token *token);
t_token			*lexer_next_token(t_lexer *lexer);
t_token			*tokenizer(char *line);
t_token			*init_token(char *value, t_token_type type);
int				*get_parser_check(void);
int				is_special(t_lexer *lexer, int i);
int				is_operator(t_lexer *lexer);
int				is_redirection(int c);

#endif