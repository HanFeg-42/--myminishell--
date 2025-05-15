#include "../../include/exec.h"

int *get_status_code()
{
    static int status;
    return (&status);
}

int *get_error_check(void)
{
    static int check = true;

    return (&check);
}
void set_exec_error(const char *msg, int nb)
{
    if (msg)
        perror(msg);
    *get_error_check() = false;
    *get_status_code() = nb;
}

void ast_advance(t_ast **current)
{
    if (*current)
        *current = (*current)->next_sibling;
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
void execute_compoud(t_ast *ast)
{
    t_ast *current;

    current = ast->first_child;
    printf("hello\n");
    while (current)
    {
        execute_pipeline(current);
        // if (!(*get_error_check()))
        //     return;
        ast_advance(&current);
        if (current)
        {
            if (current->type == AST_OR)
            {
                ast_advance(&current);
                if (!(*get_status_code()))
                    ast_advance(&current);
            }
            if (current->type == AST_AND)
            {
                ast_advance(&current);
                if (*get_status_code())
                    ast_advance(&current);
            }
        }
        else
            break;
    }
}

t_pipe *init_pipes(t_ast *ast)
{
    t_pipe *pipeline;
    int i;

    pipeline = ft_malloc(sizeof(t_pipe));
    if (!pipeline)
        return (NULL);
    pipeline->num_of_cmds = ast_size(ast);
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
    return (pipeline);
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
        printf("helllo \n");
        *get_status_code() = 0;
        execute_command(current, pipeline, i);
        ast_advance(&current);
        i++;
    }
    close_pipes(pipeline);
    wait_children(pipeline);
}

void execute_command(t_ast *ast, t_pipe *pipeline, int i)
{
    t_ast *current;

    printf("aaaaaaaaaaa\n");

    current = ast->first_child;
    if (current->type == AST_SIMPLE_CMD)
    {
        execute_simple_cmd(current, pipeline, i);

    }
    else
        execute_subshell(current, pipeline, i);
}
int envp_size(t_envp **old_envp)
{
    int size = 0;
    t_envp *current;
    
    current = *old_envp;

    while (current)
    {
        size++;
        current = current->next;
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
    printf("size %d \n",size);
    printf("envp\n");
    envp = malloc(sizeof(char *) * (size + 1));
    if (!envp)
        return (NULL);
    current = *old_envp;
    size = 0;
    while (current)
    {
        holder = ft_strjoin(current->key, "=");
        holder = ft_strjoin(holder, "\"");
        holder = ft_strjoin(holder, current->value);
        holder = ft_strjoin(holder, "\"");
        envp[size] = ft_strdup(holder);
        size++;
        current = current->next;
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
    printf("seeeeee\n");
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
        else if (i == pipeline->num_of_cmds - 1)
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

    command = ft_strdup(cmd);
    printf("batat \n");
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
    exit(127);
}
void exec_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    char **envp;
    char *pathname;
    int type;

    type = type_cmd(ast->args[0]);

    if (type == -1)
    {
        envp = convert_envp();         // wait till u fork
        pipeline->counter++;
        pipeline->pids[pipeline->counter] = fork();
        if (pipeline->pids[pipeline->counter] == 0)
        {
            redirect_to_pipe(pipeline, i); // inside fork;
            printf ("Hhhhhhhh\n");
            printf("%s\n",ast->args[0]);
            if(!envp)
                printf("laaaaaaaaaaaa\n");
            pathname = get_path(ast->args[0], envp);
            if (!pathname)
                handle_cmd_error(ast->args[0]);
            execve(pathname, ast->args, envp);
            exit(126);
        }
        else
            return;
    }
    else
        execute_builtins(type, ast->args);
}
////////////////////////////////////////////////////////////////////////////////////////

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
        close_redirect(fds, i - 1);
        // error(); // come back here
    }
}
void redirect_io(int fd, t_file *file)
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

void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    int *fds;

    if(ast->redirect)
    {
    fds = open_redirects(ast->redirect);
    if (!fds)
        set_exec_error(NULL, 1);
    }
    printf("starts\n");
    exec_cmd(ast, pipeline, i);
    // if(ast->redirect)
    //     close_redirect(fds,num_of_redirects(ast->redirect));
}

void execute_subshell(t_ast *ast, t_pipe *pipeline, int i)
{
    int status;
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
