#include "../../../include/minishell.h"

int *get_parser_check(void)
{
    static int check = true;

    return (&check);
}