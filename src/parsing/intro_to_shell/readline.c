#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    // printf("^C");
}

int main()
{
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("\033[38;2;255;105;180mMinishell > \033[0m");
        if (!line)
            break;
        printf("This is what you wrote:: %s\n", line);
        add_history(line);
        free(line);
    }
    return (0);
}