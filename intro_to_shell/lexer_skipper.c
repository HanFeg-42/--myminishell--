#include "../include/minishell.h"

t_token *lexer_skip_comment(t_lexer *lexer)
{
    char *comment;
    int i;

    i = 0;
    while (lexer->line[lexer->i + i])
        i++;
    comment = ft_malloc(sizeof(char) * i + 1);
    if (!comment)
        clean_exit(lexer, NULL);
    i = 0;
    while (lexer->c)
    {
        comment[i] = lexer->c;
        lexer_advance(lexer);
        i++;
    }
    comment[i] = '\0';
    return (init_token(comment, COMMENT));
}

void lexer_skip_whitespaces(t_lexer *lexer)
{
    while (ft_issapce(lexer->c))
        lexer_advance(lexer);
}

int is_special(int c)
{
	if (c == '\0' || ft_issapce(c)
        || c == '$' || c == '*' || c == '&' || c == '|'
        || c == '>' || c == '<' || c == 34 || c == 39
        || c == '(' || c == ')' || c == '{' || c == '}')
		return (1);
	return (0);
}

int is_operator(int c)
{
	if (c == '|' || c == '&')
		return (1);
	return (0);
}

int is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int get_q_size(t_lexer *lexer)
{
    int i;

    i = 0;
    while (lexer->line[lexer->i + i] != '"')
        i++;
    return (i);
}
