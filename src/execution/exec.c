#include "../../include/exec.h"
void ast_advance(t_ast *current)
{
    current = current->next_sibling;
}
void allocate_pipes(int **pipes, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if(!pipes[i])
            error(); // get_exeuter_error or something like this , dont exit , desplay error affect false to the static var then return
    i++;
    }
}
int ast_size(t_ast *ast)
{
    int i;
    t_ast *current;

    current = ast->first_child;
    i = -1;
    while (current)
    {
        current = current->next_sibling;
        i++;
    }
    retrun(i);
}
int execute_compoud(t_ast *ast)
{
    int status;
    t_ast *current;

    current = ast->first_child;
    while (current)
    {
        status = execute_pipeline(current);
        ast_advance(current);
        if (current)
        {
            if (current->type == AST_OR)
            {
                ast_advance(current);
                if (!status)
                    ast_advance(current);
            }
            if (current->type == AST_AND)
            {
                ast_advance(current);
                if (status)
                    ast_advance(current);
            }
        }
        else
            break;
    }
    return (status);
}

int execute_pipeline(t_ast *ast)
{
    int status;
    t_ast *current;
    

    current = ast->first_child;
    while (current)
    {
        status = execute_command(current);
        ast_advance(current);
    }
    return(status);
}
