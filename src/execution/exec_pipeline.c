#include "../../include/exec.h"

void execute_pipeline(t_ast *ast)
{
    t_pipe *pipeline;
    t_ast *current;
    int i;

    pipeline = init_pipes(ast);
    if (!pipeline)
    {
        set_exec_error(NULL, 1);
        return;
    }
    create_pipes(pipeline);
    if (!(*get_error_check()))
        return;
    current = ast->first_child;
    i = 0;
    while (current)
    {
        *get_status_code() = 0;
        execute_command(current, pipeline, i);
        ast_advance(&current);
        i++;
    }
    // close_pipes(pipeline);
    // wait_children(pipeline);
}

t_pipe *init_pipes(t_ast *ast)
{
    t_pipe *pipeline;
    int i;

    pipeline = ft_malloc(sizeof(t_pipe));
    if (!pipeline)
        return (NULL);
    pipeline->num_of_cmds = ast_size(ast);
    printf("num of commands %d\n", pipeline->num_of_cmds);
    if (pipeline->num_of_cmds != 1)
    {
        pipeline->pipes = ft_malloc(sizeof(int *) * (pipeline->num_of_cmds - 1));
        if (!pipeline->pipes)
            return (NULL);
        i = 0;
        while (i < pipeline->num_of_cmds)
        {
            pipeline->pipes[i] = ft_malloc(sizeof(int) * 2);
            if (!pipeline->pipes[i])
                return (NULL); // get_exeuter_error or something like this , dont exit , desplay error affect false to the static var then return
            i++;
        }
    }
    pipeline->pids = malloc(sizeof(int) * pipeline->num_of_cmds);
    if (!pipeline->pids)
        return (NULL);
    pipeline->counter = -1;
    pipeline->saved_stdin = dup(STDIN_FILENO);
    pipeline->saved_stdout = dup(STDOUT_FILENO);
    return (pipeline);
}

void create_pipes(t_pipe *pipeline)
{
    int i;
    i = 0;

    while (i < pipeline->num_of_cmds - 1)
    {
        if (pipe(pipeline->pipes[i]) < 0)
            set_exec_error("pipe", 1);
        i++;
    }
}

int ast_size(t_ast *ast)
{
    int i;
    t_ast *current;
    current = ast->first_child;
    i = 0;
    while (current)
    {
        current = current->next_sibling;
        i++;
    }
    return (i);
}
void close_pipes(t_pipe *pipeline)
{
    int i;

    i = 0;
    while (i < pipeline->num_of_cmds - 1)
    {
        close(pipeline->pipes[i][0]);
        close(pipeline->pipes[i][1]);
        i++;
    }
}

void wait_children(t_pipe *pipeline)
{
    int i;
    int status;

    i = 0;
    while (i < pipeline->counter)
    {
        waitpid(pipeline->pids[i], &status, 0);
        // if (i == pipeline->n - 1)
        // {
        //     if (WIFEXITED(status))
        //         *get_status_code() = WEXITSTATUS(status);
        // }
        i++;
    }
}