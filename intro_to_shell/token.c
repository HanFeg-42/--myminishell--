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
    int hard_code;

    lexer = init_lexer(line);
    token = NULL;
    hard_code = 0;
    while ((token = lexer_next_token(lexer)))
    {
        printf("token : %s \ttype : %d\n", token->value, token->type);
        if (!hard_code)
            token->prev = NULL;
        if (token->value)
            free(token->value);
        free(token);
    }
    free(lexer->line);
    free(lexer);
    return (NULL);
}
