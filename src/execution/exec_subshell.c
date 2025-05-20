#include "../../include/exec.h"

void execute_subshell(t_ast *ast, t_pipe *pipeline)
{
    int *fds;

    if (ast->redirect)
        fds = open_redirects(ast->redirect);
    pipeline->counter++;
    pipeline->pids[pipeline->counter]= fork();
    if (pipeline->pids[pipeline->counter] == 0)
    {
        execute_compoud(ast->first_child);
    }
    dup2(pipeline->saved_stdout,STDOUT_FILENO);
    dup2(pipeline->saved_stdin,STDIN_FILENO);
    
}