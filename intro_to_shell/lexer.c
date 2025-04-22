#include "../include/minishell.h"

t_token *lexer_next_token(t_lexer *lexer)
{
	if (*get_parser_check() == false)
		return (NULL);
	while (lexer->c)
	{
		lexer_skip_whitespaces(lexer);
		if (is_operator(lexer->c))
			return (lexer_operator(lexer));
		if (is_redirection(lexer->c))
			return (lexer_redirection(lexer));
		if (lexer->c == '#') // should advance all next characters without saving it as a token
			return (lexer_advance_with(lexer, lexer_skip_comment(lexer))); // eroooooooooooooooooooooooooooooooooooor
		if (!is_special(lexer->c)) // is_metacharacterrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
			return (lexer_advance_with(lexer, lexer_get_word(lexer)));
		if (lexer->i == lexer->line_size - 1)
			return (NULL);
	}
	return (NULL);
}

t_token *lexer_operator(t_lexer *lexer)
{
	if (lexer->c == '&')
	{
		if (lexer->line[lexer->i + 1] == '&')
			return (lexer_advance_with2(lexer, init_token(ft_strdup("&&"), AND)));
		throw_error("&");
	}
	if (lexer->c == '|')
	{
		if (lexer->line[lexer->i + 1] == '|')
		return (lexer_advance_with2(lexer, init_token(ft_strdup("||"), OR)));
		return (lexer_advance_current(lexer, PIPE));
	}
	if (lexer->c == '(')
		return (lexer_advance_current(lexer, OPAREN));
	if (lexer->c == ')')
		return (lexer_advance_current(lexer, CPAREN));
	return (NULL);
}

t_token *lexer_redirection(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		if (lexer->line[lexer->i + 1] == '>')
			return (lexer_advance_with2(lexer, init_token(ft_strdup(">>"), APPEND)));
		return (lexer_advance_current(lexer, OUTPUT_RED));
	}
	if (lexer->c == '<')
	{
		if (lexer->line[lexer->i + 1] == '<')
			return (lexer_advance_with2(lexer, init_token(ft_strdup("<<"), HERE_DOC)));
		return (lexer_advance_current(lexer, INPUT_RED));
	}
	return (NULL);
}
