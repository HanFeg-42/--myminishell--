#include "../../include/exec.h"


void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    int *fds;

    if(ast->redirect)
    {
    fds = open_redirects(ast->redirect);
    if (!fds)
        set_exec_error(NULL, 1);
    }
    printf("starts SIMPLE CMD EXEC \n");
    exec_cmd(ast, pipeline, i);
    dup2(pipeline->saved_stdout,STDOUT_FILENO);
    dup2(pipeline->saved_stdin,STDIN_FILENO);
    // if(ast->redirect)
    //     close_redirect(fds,num_of_redirects(ast->redirect));
}
int *open_redirects(t_file *redirect)
{
    t_file *current;
    int *fds;
    int i;

    fds = ft_malloc(sizeof(int) * num_of_redirects(redirect));
    if (!fds)
        return (NULL);
    i = 0;
    current = redirect;
    while (current)
    {
        open_file(current, fds, i);
        redirect_io(fds[i], current);
        i++;
        current = current->next;
    }
    return (fds);
}
int num_of_redirects(t_file *lst)
{
    int len;
    t_file *current;

    if(!lst)
        return (0);

    current = lst;

    len = 0;
    while (current)
    {
        current = current->next;
        len++;
    }
    printf("num of redirects %d \n",len);
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
        fds[i] = open(file->filename, O_RDONLY, 0644);
    else if (file->type == OUTPUT_RED)
        fds[i] = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    // else      // dont forget heredoc
    if (fds[i] < 0)
    {
        close_redirect(fds, i - 1);
        // error(); // come back here
    }
}
void redirect_io(int fd, t_file *file)
{
    if (file->type == APPEND || (file->type == OUTPUT_RED))
        dup2(fd, STDOUT_FILENO);
    else if ((file->type == INPUT_RED))
        dup2(fd, STDIN_FILENO);
    // ELSE heredoc
}