#include "../../include/exec.h"

void exec_cmd(t_ast *ast, t_cmd *cmd)
{
    cmd->pipeline->counter++;
    cmd->pipeline->pids[cmd->pipeline->counter] = fork();
    if (cmd->pipeline->pids[cmd->pipeline->counter] < 0)
    {
        set_exec_error("fork", 1);
        return;
    }
    if (cmd->pipeline->pids[cmd->pipeline->counter] == 0)
    {
        if (!(*get_parser_check()))
        {
            close_all_pipes(cmd->pipeline);
            exit(EXIT_FAILURE);
        }
        handle_process(ast, cmd);
    }
}

void handle_process(t_ast *ast, t_cmd *cmd)
{
    if (ast->redirect)
    {
        cmd->num_of_redirect = num_of_redirects(ast->redirect);
        cmd->fds = open_redirects(ast->redirect);
        if (!(*get_error_check()))
            exit(1);
    }
    setup_process_pipes(ast, cmd->pipeline, cmd->pos);
    if (!ast->args)
        exit(EXIT_SUCCESS);
    cmd->type = type_cmd(ast->args[0]);
    if (cmd->type != -1)
    {
        execute_builtins(cmd->type, ast->args);
        free_all();
        exit(*get_status_code());
    }
    cmd->envp = convert_envp();
    cmd->pathname = get_path(ast->args[0], cmd->envp);
    if (!cmd->pathname)
        handle_cmd_error(ast->args[0]);
    execve(cmd->pathname, ast->args, cmd->envp);
    close_redirect(cmd->fds, cmd->num_of_redirect);
    exit(126);
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
    if (!cmd[0])
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
    ft_putstr_fd(" : command not found", 2);
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
