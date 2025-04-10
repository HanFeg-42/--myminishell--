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
    // printf("\n"); // katje3 lster
    printf("%s\n", err); //katrprinti l error
    rl_replace_line("", 0); // ila knt deja katba chi haja kat7ydha
    rl_on_new_line(); // kat3yt l readline 3awtani walakin makat affichiha ta kanpressi chi key
    // rl_redisplay(); // hai kataffichi lia dek lmsg li 3atya l readline once the signal ddar
    // exit(1);
}
