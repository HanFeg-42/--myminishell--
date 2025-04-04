#include "../include/minishell.h"

t_token *init_token(char *value, int type)
{
    t_token *tok;

    tok = malloc(sizeof(t_token));
    if (!tok)
        return (NULL);
    tok->value = value;
    tok->type = type;
    tok->next = NULL;
    tok->prev = NULL;
    return (tok);
}

t_token *tokenize(char *line)
{
    t_lexer *lexer;
    t_token *token;
    t_token *tok_head;

    lexer = init_lexer(line);
    tok_head = init_token(NULL, 0);
    token = NULL;
    while ((token = lexer_next_token(lexer)))
    {
        printf("token : %s \ttype : %d\n", token->value, token->type);
        token_addback(&tok_head, token);
        if (token->value && token->type != EXPANSION)
            free(token->value);
        if (token)
            free(token);
    }
    if (lexer->line)
        free(lexer->line);
    if (lexer)
        free(lexer);
    return (NULL);
}

void token_addback(t_token **tok_head, t_token *token)
{

}

t_token *token_last(t_token *tok_head)
{
    
}
