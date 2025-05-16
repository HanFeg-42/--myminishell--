#include "../../include/exec.h"

void execute_command(t_ast *ast, t_pipe *pipeline, int i)
{
    t_ast *current;

    current = ast->first_child;
    if (current->type == AST_SIMPLE_CMD)
    {
        execute_simple_cmd(current, pipeline, i);
    }
    else
        execute_subshell(current, pipeline);
}