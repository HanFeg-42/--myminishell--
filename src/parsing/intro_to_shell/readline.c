#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int sig)
{
    (void)sig;
    printf("\n");
    // rl_replace_line("", 0); // hadi kima glt ma3ndha tachi dawr flhayat
    rl_on_new_line();
    rl_redisplay();
}

int main()
{
    char *line;

    signal(SIGINT, handler);
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