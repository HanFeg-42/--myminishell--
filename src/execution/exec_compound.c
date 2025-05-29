#include "../../include/exec.h"

int *get_status_code()
{
    static int status = 0;
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

    if (!ast)
        return;
    if (!(*get_parser_check()))
    {
        *get_status_code() = 2;
		return ;
    }
    current = ast->first_child;
    while (current)
    {
        execute_pipeline(current);
        ast_advance(&current);
        if (current)
        {
            if (current->type == AST_OR)
            {
                ast_advance(&current);
                if (!(*get_status_code()))
                    ast_advance(&current);
            }
            if (current && current->type == AST_AND)
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
