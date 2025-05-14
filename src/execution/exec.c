#include "../../include/exec.h"
void ast_advance(t_ast *current)
{
    current = current->next_sibling;
}
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
    i = 0;
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
    pipeline->pipes = ft_malloc(sizeof(int *) * (pipeline->num_of_cmds - 1));
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
    pipeline->counter = -1;
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
int envp_size(t_envp **old_envp)
{
    int size;
    t_envp *curent;

    current = *envp;
    size = 0;

    while (curent)
    {
        size++;
        curent = curent->next;
    }
    return (size);
}
char **convert_envp()
{
    char **envp;
    t_envp **old_envp;
    int size;
    t_envp *current;
    char *holder;

    old_envp = get_env_head();
    size = envp_size(old_envp);
    envp = malloc(sizeof(char *) * (size + 1));
    if (!envp)
        ;
    return (NULL);
    current = *old_envp;
    size = 0;
    while (current)
    {
        holder = ft_strjoin(current->key, "=");
        holder = ft_strjoin(holder, current->value);
        envp[size] = ft_strdup(holder);
        size++;
    }
    envp[size] = NULL;
    return (envp);
}
static char *concat_path(char *path, char *cmd)
{
    char *fullpath;
    char *tmp;

    if (!path || !cmd)
        return (NULL);
    tmp = ft_strjoin(path, "/");
    if (!tmp)
        return (NULL);
    fullpath = ft_strjoin(tmp, cmd);
    free(tmp);
    return (fullpath);
}

char *find_path(char **paths, char *cmd)
{
    int i;
    char *fullpath;

    i = 0;
    while (paths[i])
    {
        fullpath = concat_path(paths[i], cmd);
        if (fullpath && access(fullpath, X_OK) == 0)
        {
            return (fullpath);
        }
        i++;
    }
    return (NULL);
}
char *get_path(char *cmd, char **envp)
{
    char **paths;
    int i;

    if (!cmd || !envp)
        return (NULL);
    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    return (find_path(paths, cmd));
}
void redirect_to_pipe(t_pipe *pipeline, int i)
{
    if (pipeline->num_of_cmds != 1)
    {
        if (i == 0)
            dup2(pipeline->pipes[i][1], STDOUT_FILENO);
        else if (i == pipeline->num_of_cmds)
            dup2(pipeline->pipes[i - 1][0], STDIN_FILENO);
        else
        {
            dup2(pipeline->pipes[i - 1][0], STDIN_FILENO);
            dup2(pipeline->pipes[i][1], STDOUT_FILENO);
        }
    }
}
int type_cmd(char *cmd)
{
    char *command;
    char *position;

    command = cmd;
    position = ft_strrchr(cmd, '/');
    if (position)
    {
        command = ft_strdup(position + 1);
    }
    return (is_builtin(command));
}
void handle_cmd_error(char *command)
{
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": command not found", 2);
    ft_putstr_fd("\n", 2);
    // exit->status = 127 //
}
void exec_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    char **envp;
    char *pathname;
    int type;

    type = type_cmd(ast->args[0]);

    if (type == -1)
    {
        pipeline->counter++;
        pipeline->pids[pipeline->counter] = fork();
        if (pipeline->pids[pipeline->counter] == 0)
        {
            redirect_to_pipe(pipeline, i); // inside fork;
            envp = convert_envp();         // wait till u fork
            pathname = get_path(command[0], envp);
            if (!pathname)
                handle_cmd_error(command[0]);
            execve(pathname, ast->args, envp);
            // exit->status = 126 //
        }
    }
    else
        execute_builtins(type, ast->args);
}

int execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    int status;
    int *fds;

    fds = open_redirects(ast->redirect);
    exec_cmd(ast, pipeline, i);
}

int num_of_redirects(t_file *lst)
{
    int len;
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
        fds[i] = open(file->filename, O_CREAT | O_RDONLY | O_APPEND, 0644);
    else if (file->type == INPUT_RED)
        fds[i] = open(file->filename, O_RDONLY, 0644);
    else if (file->type == OUTPUT_RED)
        fds[i] = open(file->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    // else      // dont forget heredoc
    if (fds[i] < 0)
    {
        close_redirects(fds, i - 1);
        error(); // come back here
    }
}
void redirect(int fd, t_file *file)
{
    if (file->type == APPEND || (file->type == OUTPUT_RED))
        dup2(fd, STDOUT_FILENO);
    else if ((file->type == OUTPUT_RED))
        dup2(fd, STDOUT_FILENO);
    // ELSE heredoc
}
int *open_redirects(t_file *redirect)
{
    t_file *current;
    int *fds;
    int i;

    fds = ft_malloc(sizeof(int) * num_of_redirects(redirect));
    if (!fds)
        error(); // handle this
    i = 0;
    current = redirect;
    while (current)
    {
        open_file(current, fds, i);
        redirect(fds[i], current);
        i++;
        current = current->next;
    }
    return (fds);
}

int execute_subshell(t_ast *ast, t_pipe *pipeline, int i)
{
    int status;
    int *fds;
    int fd;

    if (ast->redirect)
        fds = open_redirects(ast->redirect);
    fd = fork();
    if (fd == 0)
    {
        status = execute_compoud(ast->first_child);
    }
    return (status);
}
