#include "../../include/exec.h"

int *get_status_code()
{
    static int status;
    return (&status);
}

int *get_error_check(void)
{
    static int check = true;

    return (&check);
}
void set_exec_error(const char *msg, int nb)
{
    if (msg)
        perror(msg);
    *get_error_check() = false;
    *get_status_code() = nb;
}

void ast_advance(t_ast **current)
{
    if (*current)
        *current = (*current)->next_sibling;
}


void execute_compoud(t_ast *ast)
{
    t_ast *current;
    if(!ast)
    return;

    current = ast->first_child;
    while (current)
    {
        execute_pipeline(current);
        // if (!(*get_error_check()))
        //     return;
        printf("\n exit status %d \n", *get_status_code());
        ast_advance(&current);
        if (current)
        {
            if (current->type == AST_OR)
            {
                ast_advance(&current);
                if (!(*get_status_code()))
                    ast_advance(&current);
            }
            if (current->type == AST_AND)
            {
                ast_advance(&current);
                if (*get_status_code())
                    ast_advance(&current);
            }
        }
        else
            break;
    }
}
















////////////////////////////////////////////////////////////////////////////////////////

