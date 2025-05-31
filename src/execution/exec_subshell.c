#include "../../include/exec.h"

void execute_subshell(t_ast *ast, t_pipe *pipeline)
{
    int *fds;

    fds = NULL;
    pipeline->counter++;
    pipeline->pids[pipeline->counter]= fork();
    if (pipeline->pids[pipeline->counter] < 0)
    {
        set_exec_error("fork", 1);
        return;
    }
    if (pipeline->pids[pipeline->counter] == 0)
    {
        if (ast->redirect)
            fds = open_redirects(ast->redirect);
        execute_compoud(ast->first_child);
        close_redirect(fds,num_of_redirects(ast->redirect));
        exit(*get_status_code());
    }
}
