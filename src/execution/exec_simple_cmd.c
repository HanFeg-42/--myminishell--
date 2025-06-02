#include "../../include/exec.h"

void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    t_cmd *cmd;

    cmd = ft_malloc(sizeof(t_cmd));
    if (!cmd)
        return (set_exec_error("malloc", 1));
    expand(ast);
    cmd->pos = i;
    cmd->pipeline = pipeline;
    if (ast->args)
    {
        cmd->type = type_cmd(ast->args[0]);
        if (cmd->type != -1 && cmd->pipeline->num_of_cmds == 1)
        {
            if (!(*get_parser_check()))
            {
                *get_status_code() = 1;
                return;
            }
            execute_single_built(cmd, ast);
            return;
        }
    }
    exec_cmd(ast, cmd);
}

void execute_single_built(t_cmd *cmd, t_ast *ast)
{
    cmd->saved_stdin = dup(STDIN_FILENO);
    cmd->saved_stdout = dup(STDOUT_FILENO);
    if (ast->redirect)
    {
        cmd->num_of_redirect = num_of_redirects(ast->redirect);
        cmd->fds = open_redirects(ast->redirect);
        if (!(*get_error_check()))
            return;
        close_redirect(cmd->fds, cmd->num_of_redirect - 1);
    }
    execute_builtins(cmd->type, ast->args);
    restor_standars(cmd);
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
        set_exec_error("malloc failed", 1);
        return (NULL);
    }
    i = 0;
    current = redirect;
    while (current)
    {
        open_file(current, fds, i);
        if (!(*get_error_check()))
            return (NULL);
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
    else if (file->type == INPUT_RED || file->type == HERE_DOC)
        fds[i] = open(file->filename, O_RDONLY);
    else
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
    else if (file->type == INPUT_RED || file->type == HERE_DOC)
        dup2(fd, STDIN_FILENO);
}
