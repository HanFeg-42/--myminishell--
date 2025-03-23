#include "../include/minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;

    lexer->line = line;
    lexer->i = 0;
    lexer->c = line[0];
    return (lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if (lexer && lexer->c && lexer->line[lexer->i + 1])
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
    }
}

void lexer_skip_whitespaces(t_lexer *lexer)
{
    while (is_space(lexer->c))
        lexer_advance(lexer);
}

