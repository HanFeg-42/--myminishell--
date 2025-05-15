#include "../../include/exec.h"

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
            envp = convert_envp();         // wait till u fork
            redirect_to_pipe(pipeline, i); // inside fork;
            write (2,"after redirct to pipe \n",24);
            printf("%s\n",ast->args[0]);
            if(!envp)
                write (2,"envp failed \n",14);
            pathname = get_path(ast->args[0], envp);
            if (!pathname)
                handle_cmd_error(ast->args[0]);
            execve(pathname, ast->args, envp);
            exit(126);
        }
    }
    else
        execute_builtins(type, ast->args);
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
        write(2,"finishing redirecting to pipes\n",32);
    }
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
char *concat_path(char *path, char *cmd)
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

void handle_cmd_error(char *command)
{
    ft_putstr_fd(command, 2);
    ft_putstr_fd(": command not found", 2);
    ft_putstr_fd("\n", 2);
    exit(127);
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


