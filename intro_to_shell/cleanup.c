#include "../include/minishell.h"

void clean_exit(t_lexer *lexer, t_token *token)
{
    (void)lexer;
    (void)token;
    exit(1);
}


void exit_error()
{
    printf("ERROR\n");
    // exit(1);
}
void throw_error(char *err)
{
    (void)err;
    exit(1);
}
