#include "../include/minishell.h"

void handler_SIGINT(int sig)
{
    (void)sig;
    printf("\n"); // katje3 lster
    rl_replace_line("", 0); // ila knt deja katba chi haja kat7ydha
    rl_on_new_line(); // kat3yt l readline 3awtani walakin makat affichiha ta kanpressi chi key
    rl_redisplay(); // hai kataffichi lia dek lmsg li 3atya l readline once the signal ddar
}

void handler_SIGQUIT(int sig)
{
    (void)sig;
    printf("\b");
}

int main()
{
    char *line;
    t_token *token;

    signal(SIGINT, handler_SIGINT);
    signal(SIGQUIT, handler_SIGQUIT);
    while (1)
    {
        line = readline("\033[38;2;255;105;180mMinishell > \033[0m");
        if (!line || !strcmp(line, "exit"))
            break;
        printf("This is what you wrote: %s\n", line);
        token = tokenize(line);
        add_history(line);
        free(line);
        free(token);
    }
    return (0);
}