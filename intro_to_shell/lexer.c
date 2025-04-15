#include "../include/minishell.h"

t_token *lexer_next_token(t_lexer *lexer)
{
	while (lexer->c)
	{
		lexer_skip_whitespaces(lexer);
		if (lexer->c == '*')
			return (lexer_advance_current(lexer, STAR));
		if (is_operator(lexer->c))
			return (lexer_operator(lexer));
		if (is_redirection(lexer->c))
			return (lexer_redirection(lexer));
		if (ft_strchr("\"\'()", lexer->c))
			return (lexer_quote_or_paren(lexer));
		if (lexer->c == '$')
			return (lexer_advance_with(lexer, lexer_get_expansion(lexer)));
		if (lexer->c == '#')
			return (lexer_advance_with(lexer, lexer_skip_comment(lexer)));
		if (!is_special(lexer->c))
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
			return (lexer_advance_with(lexer, lexer_get_heredoc(lexer)));
		return (lexer_advance_current(lexer, INPUT_RED));
	}
	return (NULL);
}

t_token *lexer_quote_or_paren(t_lexer *lexer)
{
	if (lexer->c == '"')
	return (lexer_advance_current(lexer, DQUOTE));
	if (lexer->c == '\'')
	return (lexer_advance_current(lexer, SQUOTE));
	if (lexer->c == '(')
	return (lexer_advance_current(lexer, OPAREN));
	if (lexer->c == ')')
	return (lexer_advance_current(lexer, CPAREN));
	return (NULL);
}

// t_token *lexer_quote_or_paren(t_lexer *lexer)
// {
// 	if (lexer->c == '"')
// 		return (lexer_get_dquote(lexer));
// 	if (lexer->c == '\'')
// 		return (lexer_get_squote(lexer));
// 	if (lexer->c == '(')
// 		return (lexer_advance_current(lexer, OPAREN));
// 	if (lexer->c == ')')
// 		return (lexer_advance_current(lexer, CPAREN));
// 	return (NULL);
// }

// TO_DO : is_operator ---------------------------------------[ ]
// TO_DO : lexer_operator ------------------------------------[ ]
// TO_DO : is_redirection ------------------------------------[ ]
// TO_DO : lexer_redirection ---------------------------------[ ]
// TO_DO : lexer_quote_or_paren ------------------------------[ ]
// TO_DO :