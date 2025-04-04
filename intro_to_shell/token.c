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
    static t_token *tok_head;

    lexer = init_lexer(line);
    tok_head = lexer_next_token(lexer);
    // printf("token : %s \ttype : %d\n", tok_head->value, tok_head->type);
    token = NULL;
    while ((token = lexer_next_token(lexer)))
    {
        // printf("token : %s \ttype : %d\n", token->value, token->type);
        token_addback(&tok_head, token);
        // if (token->value && token->type != EXPANSION)
        //     free(token->value);
        // if (token)
        //     free(token);
    }
    token_print(tok_head);
    token_free_list(tok_head);
    if (lexer->line)
        free(lexer->line);
    if (lexer)
        free(lexer);
    return (NULL);
}

void token_addback(t_token **tok_head, t_token *token)
{
    t_token *last;

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

t_token *token_last(t_token *tok_head)
{
    t_token *current;

    if (!tok_head)
        return (NULL);
    current = tok_head;
    while (current->next)
        current = current->next;
    return (current);
}

void token_print(t_token *tok)
{
    t_token *head;

    head = tok;
    while (tok)
    {
        printf("%s \t===>", tok->value);
        tok = tok->next;
    }
}

void token_free_list(t_token *tok)
{
    t_token *next;

    while (tok)
    {
        next = tok->next;
        if (tok->value && tok->type != EXPANSION)
            free(tok->value);
        if (tok)
            free(tok);
        tok = next;
    }
}