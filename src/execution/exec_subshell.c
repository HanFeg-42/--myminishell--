#include "../../include/exec.h"

void execute_subshell(t_ast *ast, t_pipe *pipeline, int i)
{
    int *fds;
    int fd;

    if (ast->redirect)
        fds = open_redirects(ast->redirect);
    fd = fork();
    if (fd == 0)
    {
        execute_compoud(ast->first_child);
    }
}