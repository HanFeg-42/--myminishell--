#include "include/minishell.h"

int skip_option(char **arg, int *i)
{
    int check;
    int j;

    check = *i;
    while (arg[*i] && arg[*i][0] == '-')
    {
        j = 1;
        while (arg[*i][j] && arg[*i][j] == 'n')
            j++;
        if (arg[*i][j] == '\0')
        {
            if (arg[*i][j - 1] != 'n')
                return (false);
        }
        else
            return (false);
        (*i)++;
    }
    return (!(check == *i));
}

void echo(char **arg)
{
    int i;
    int option;

    i = 1;
    option = skip_option(arg, &i);
    while (arg[i])
    {
        ft_putstr_fd(arg[i++], STDOUT_FILENO);
        if (arg[i])
            write(1, " ", 1);
    }
    if (!option)
        write(1, "\n", 1);
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (0);
    echo(av);
}
