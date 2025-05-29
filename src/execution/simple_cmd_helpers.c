#include "../../include/exec.h"

void exec_cmd(t_ast *ast, t_pipe *pipeline, int i)
{
    char **envp;
    char *pathname;
    int *fds;
    int num_of_redirect;
    int type;

    pipeline->counter++;
    pipeline->pids[pipeline->counter] = fork();
    if (pipeline->pids[pipeline->counter] < 0)
    {
        set_exec_error("fork", 1);
        return;
    }
    if (pipeline->pids[pipeline->counter] == 0)
    {
        if (ast->redirect)
        {
            num_of_redirect = num_of_redirects(ast->redirect);
            fds = open_redirects(ast->redirect);
            if (!(*get_error_check()))
                return;
        }
        setup_process_pipes(ast, pipeline, i);
        if (!ast->args)
            exit(EXIT_SUCCESS);
        type = type_cmd(ast->args[0]);
        if (type != -1)
        {
            execute_builtins(type, ast->args);
            exit(*get_status_code());
        }
        envp = convert_envp();
        pathname = get_path(ast->args[0], envp);
        if (!pathname)
            handle_cmd_error(ast->args[0]);
        execve(pathname, ast->args, envp);
        close_redirect(fds, num_of_redirect);
        exit(126);
    }
}

void setup_process_pipes(t_ast *ast, t_pipe *pipeline, int i)
{
    if (pipeline->num_of_cmds > 1)
    {
        if (i == 0)
        {
            if (!has_output_redirection(ast->redirect))
                dup2(pipeline->pipes[i][1], STDOUT_FILENO);
        }
        else if (i == pipeline->num_of_cmds - 1)
        {
            if (!has_input_redirection(ast->redirect))
                dup2(pipeline->pipes[i - 1][0], STDIN_FILENO);
        }

        else
        {
            if (!has_input_redirection(ast->redirect))
                dup2(pipeline->pipes[i - 1][0], STDIN_FILENO);
            if (!has_output_redirection(ast->redirect))
                dup2(pipeline->pipes[i][1], STDOUT_FILENO);
        }
        close_all_pipes(pipeline);
    }
    // close(pipeline->saved_stdin);
    // close(pipeline->saved_stdout);
}

void close_all_pipes(t_pipe *pipeline)
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
int type_cmd(char *cmd)
{
    char *command;
    char *position;

    command = ft_strdup(cmd);
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
    envp = ft_malloc(sizeof(char *) * (size + 1));
    if (!envp)
        return (NULL);
    current = *old_envp;
    size = 0;
    while (current)
    {
        holder = ft_strjoin(current->key, "=");
        holder = ft_strjoin(holder, current->value);
        envp[size] = ft_strdup(holder);
        size++;
        current = current->next;
    }
    envp[size] = NULL;
    return (envp);
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
