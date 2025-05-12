#include "../../include/exec.h"
void ast_advance(t_ast *current)
{
    current = current->next_sibling;
}
// int ** allocate_pipes(int size)
// {
//     int **pipes;
//     int i;

//     pipes = ft_malloc(sizeof(int *) * size);
//     if(!pipes)
//         error();
//     i = 0;
//     while (i < size)
//     {
//         pipes[i] = ft_malloc(sizeof(int) * 2);
//         if(!pipes[i])
//             error(); // get_exeuter_error or something like this , dont exit , desplay error affect false to the static var then return
//     i++;
//     }
//     return(pipes);
// }

void create_pipes(t_pipe *pipeline)
{
    int i;
    i = 0;

    while (i < pipeline->num_of_cmds)
    {
        if (pipe(pipeline->pipes[i]) < 0)
            error();
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
t_pipe *init_pipes(t_ast *ast)
{
    t_pipe *pipeline;
    int i;

    pipeline = ft_malloc(sizeof(t_pipe));
    if (!pipeline)
        return (NULL);
    pipeline->num_of_cmds = ast_size(ast);
    pipeline->pipes = ft_malloc(sizeof(int *) * pipeline->num_of_cmds);
    if (!pipeline->pipes)
        error();
    i = 0;
    while (i < pipeline->num_of_cmds)
    {
        pipeline->pipes[i] = ft_malloc(sizeof(int) * 2);
        if (!pipeline->pipes[i])
            error(); // get_exeuter_error or something like this , dont exit , desplay error affect false to the static var then return
        i++;
    }
    return (pipeline->pipes);
}

int execute_pipeline(t_ast *ast)
{
    int status;
    t_ast *current;
    t_pipe *pipeline;
    int i;

    pipeline = init_pipes(ast);
    create_pipes(pipeline);
    current = ast->first_child;
    i = 0;
    while (current)
    {
        status = execute_command(current, pipeline, i);
        ast_advance(current);
        i++;
    }
    return (status);
}

int excute_command(t_ast *ast, t_pipe *pipeline, int i)
{
    int status;
    t_ast *current;

    if (current->type == AST_SIMPLE_CMD)
        status = execute_simple_cmd(current, i, pipeline);
    else
        status = execute_subshell(current, i, pipeline);
    return (status);
}

int execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    int status;



}

int	num_of_redirects(t_file *lst)
{
	int		len;
    t_file *current;

    current = lst;

	len = 0;
	while (current)
	{
		current = current->next;
		len++;
	}
	return (len);
}
void close_redirect(int *fds)
{
    int i;

    i=0;
    
}
int* open_redirects(t_file *redirect)
{
    t_file *current;
    int *fds;
    int i;

    fds=malloc(sizeof(int) * num_of_redirects(redirect));
    if(!fds)
        error();   // handle this
    i = 0;
    current = redirect;
    while(current)
    {
        if(current->type == APPEND)
            fds[i] = open(current->filename,O_CREAT | O_RDONLY | O_APPEND,0644);
        else if(current->type == INPUT_RED)
            fds[i] = open(current->filename,O_RDONLY,0644);
        else if(current->type ==  OUTPUT_RED)
            fds[i] = open(current->filename,O_CREAT | O_RDWR | O_TRUNC,0644);
        //else      // dont forget heredoc
        if(fds[i] < 0)
        {
            close_redirects(fds,i);
            error();   // come back here
        }
        i++;
    }
    return(fds);    
}

int execute_subshell(t_ast *ast, t_pipe *pipeline, int i)
{

}
