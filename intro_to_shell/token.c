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
    // int hard_code;

    // if (!line)
    //     exit(0);
    lexer = init_lexer(line);
    token = NULL;
    // hard_code = 0;
    while ((token = lexer_next_token(lexer)))
    {
        printf("token : %s \ttype : %d\n", token->value, token->type);
        // free(token->value);
        // free(token);
        // if (!hard_code)
        //     token->prev = NULL;
    }
    return (NULL);
}

// void print_tokens(t_token *token)
// {
//     t_token *tmp;

//     tmp = token;
//     while (condition)
//     {
//         /* code */
//     }
// }