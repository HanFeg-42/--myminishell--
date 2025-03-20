#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *line;

    while (1)
    {
        line = readline("\033[38;2;255;105;180mMinishell > \033[0m");
        printf("This is what you wrote:: %s\n", line);
        
        free(line);
    }
    return (0);
}