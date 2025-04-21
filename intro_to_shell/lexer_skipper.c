#include "../include/minishell.h"

// t_token *lexer_skip_comment(t_lexer *lexer)
// {
//     char *comment;
//     int i;

//     i = 0;
//     while (lexer->line[lexer->i + i])
//         i++;
//     comment = ft_malloc(sizeof(char) * i + 1);
//     if (!comment)
//         clean_exit(lexer, NULL);
//     i = 0;
//     while (lexer->c)
//     {
//         comment[i] = lexer->c;
//         lexer_advance(lexer);
//         i++;
//     }
//     comment[i] = '\0';
//     return (init_token(comment, COMMENT));
// }

t_token *lexer_skip_comment(t_lexer *lexer)
{
    while (lexer->c)
        lexer_advance(lexer);
    return (NULL);
}


void lexer_skip_whitespaces(t_lexer *lexer)
{
    while (ft_issapce(lexer->c))
        lexer_advance(lexer);
}

int is_special(int c)
{
	if (c == '\0' || ft_issapce(c)
        || c == '&' || c == '|'
        || c == '>' || c == '<'
        || c == '(' || c == ')'
        || c == '#')
		return (1);
	return (0);
}

int is_operator(int c)
{
	if (c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int get_q_size(t_lexer *lexer, int quote)
{
    int i;

    i = 0;
    if (lexer->line[lexer->i] == '\0')
    {
        throw_error("unclosed quotes!");
        return (0);
    }
    while (lexer->line[lexer->i + i] && lexer->line[lexer->i + i] != quote)
    {
        if (lexer->i + i == lexer->line_size - 1)
            throw_error("unclosed quotes!");
        i++;
    }
    return (i);
}
int get_word_size(t_lexer *lexer)
{
    int i;

    i = 0;
    while (!is_special(lexer->line[lexer->i + i]))
    {
        if (lexer->line[lexer->i + i] == '"')
            advance_to_next_quote(lexer, &i, '"');
        else if (lexer->line[lexer->i + i] == '\'')
            advance_to_next_quote(lexer, &i, 39);
        if (lexer->line[lexer->i + i] == '\0')
            break;
        i++;
    }
    if (*get_parser_check() == false)
        return (0);
    return (i);
}

void    advance_to_next_quote(t_lexer *lexer, int *i, int quote)
{
    if (*get_parser_check() ==  false)
        return ;
    (*i)++;
    if (lexer->line[lexer->i + (*i)] == '\0')
    {
        throw_error("Unclosed quotes!");
        return ;
    }
    while (lexer->line[lexer->i + (*i)] && lexer->line[lexer->i + (*i)] != quote)
    {
        if (lexer->i + (*i) == lexer->line_size - 1)
            throw_error("unclosed quotes!");
        (*i)++;
    }
}
