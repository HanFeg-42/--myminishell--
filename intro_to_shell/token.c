#include "../include/minishell.h"

t_token *init_token(char *value, int type)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->value = value;
    tok->type = type;
    return (tok);
}

t_token *tokenize(char *line)
{
    t_lexer *lexer;
    t_token *token;

    if (!line)
        exit(0);
    lexer = init_lexer(line);
    token = NULL;
    while ((token = lexer_next_token(lexer))->type)
    {
        ft_printf("token : %s type : %d\n", token->value, token->type);
    }
    return (token);
}