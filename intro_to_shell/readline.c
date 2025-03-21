#include "../include/minishell.h"

void handler_SIGINT(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0); // hadi kima glt ma3ndha tachi dawr flhayat
    rl_on_new_line();
    rl_redisplay();
}

void handler_SIGQUIT(int sig)
{
    (void)sig;
    printf("\b");
}

int main()
{
    char *line;

    signal(SIGINT, handler_SIGINT);
    signal(SIGQUIT, handler_SIGQUIT);
    while (1)
    {
        line = readline("\033[38;2;255;105;180mMinishell > \033[0m");
        if (!line || !strcmp(line, "exit"))
            break;
        printf("This is what you wrote:: %s\n", line);
        add_history(line);
        free(line);
    }
    return (0);
}