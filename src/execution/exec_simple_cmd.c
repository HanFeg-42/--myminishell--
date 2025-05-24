#include "../../include/exec.h"

void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    int type;

    type = type_cmd(ast->args[0]);
    if (type != -1)
    {
        execute_builtins(type, ast->args);
        return;
    }
    exec_cmd(ast, pipeline, i);
}
int *open_redirects(t_file *redirect)
{
    t_file *current;
    int *fds;
    int i;
    int num_of_redirect;

    num_of_redirect = num_of_redirects(redirect);
    fds = ft_malloc(sizeof(int) * num_of_redirect);
    if (!fds)
    {
        set_exec_error("Memory allocation failed", 1);
        return(NULL) ;
    }
    i = 0;
    current = redirect;
    while (current)
    {
        open_file(current, fds, i);
        if (!(*get_error_check()))
            return(NULL);
        redirect_io(fds[i], current);
        i++;
        current = current->next;
    }
    return (fds);
    // close_redirect(fds, num_of_redirect);
}
int num_of_redirects(t_file *lst)
{
    int len;
    t_file *current;

    if (!lst)
        return (0);

    current = lst;

    len = 0;
    while (current)
    {
        current = current->next;
        len++;
    }
    return (len);
}
void close_redirect(int *fds, int i)
{
    while (i >= 0)
    {
        close(fds[i]);
        i--;
    }
}
void open_file(t_file *file, int *fds, int i)
{
    if (file->type == APPEND)
        fds[i] = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else if (file->type == INPUT_RED)
        fds[i] = open(file->filename, O_RDONLY);
    else if (file->type == OUTPUT_RED)
        fds[i] = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fds[i] < 0)
    {
        close_redirect(fds, i - 1);
        set_exec_error(file->filename, 1);
    }
}

void redirect_io(int fd, t_file *file)
{
    if (file->type == APPEND || file->type == OUTPUT_RED)
        dup2(fd, STDOUT_FILENO);
    else if (file->type == INPUT_RED)
        dup2(fd, STDIN_FILENO);
}


// if (ast->redirect)
    // {
    //     open_redirects(ast->redirect);
    //     if (!(*get_error_check()))
    //         return;
    // }