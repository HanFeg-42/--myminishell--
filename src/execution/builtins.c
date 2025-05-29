#include "../../include/exec.h"

int is_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "echo"))
        return (ECHO);
    if (!ft_strcmp(cmd, "cd"))
        return (CD);
    if (!ft_strcmp(cmd, "pwd"))
        return (PWD);
    if (!ft_strcmp(cmd, "export"))
        return (EXPORT);
    if (!ft_strcmp(cmd, "unset"))
        return (UNSET);
    if (!ft_strcmp(cmd, "env"))
        return (ENV);
    // if (!ft_strcmp(cmd, "exit"))
    //     return (EXIT);
    return (-1);
}
void execute_builtins(int type, char **args)
{
    if (type == ECHO)
        return (execute_echo(args));
    if (type == CD)
        return (execute_cd(args));
    if (type == PWD)
        return (execute_pwd());
    if (type == EXPORT)
        return (execute_export(args));
    if (type == UNSET)
        return (execute_unset(args));
    if (type == ENV)
        return (execute_env());
    // if(type == EXIT)
    //     return (execute_exit());
}
void set_error(char *str)
{
    if (str)
        ft_putstr_fd(str, 2);
    set_exec_error(NULL, 1);
}
void update_env(char *old_pwd, char *new_pwd)
{
    char **elems;

    elems = ft_malloc(sizeof(char *) * 3);
    if (!elems)
    {
        set_exec_error("malloc faillure :", 1);
        free(new_pwd);
        free(old_pwd);
        return;
    }
    elems[0] = ft_strjoin("PWD=", new_pwd);
    elems[1] = ft_strjoin("OLDPWD=", old_pwd);
    elems[2] = NULL;
    execute_export(elems);
}
void execute_cd(char **args)
{
    char *old_pwd;
    char *new_pwd;
    char *path;

    if (!args[1])
    {
        path = ft_getenv("HOME");
        if (!path)
            return (set_error("cd: HOME not set\n"));
    }
    else if (args[2])
        return (set_error("cd: too many arguments\n"));
    else
        path = args[1];
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (set_exec_error("getcwd error", 1));
    if (!args || chdir(path) != 0)
        return (free(old_pwd), set_exec_error("cd", 1));
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
        return (set_exec_error("getcwd error", 1));
    update_env(old_pwd, new_pwd);
}
void execute_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        set_exec_error("getcwd error", 1);
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
void execute_env()
{
    t_envp **envp;
    t_envp *current;

    envp = get_env_head();
    current = *envp;

    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void swap_nodes(t_envp *curr, t_envp *node)
{
    char *temp_key = curr->key;
    char *temp_value = curr->value;

    curr->key = node->key;
    curr->value = node->value;
    node->key = temp_key;
    node->value = temp_value;
}

void sort_envp(t_envp **head)
{
    t_envp *curr;
    t_envp *node;

    curr = *head;
    while (curr)
    {
        node = curr->next;
        while (node)
        {
            if (ft_strcmp(curr->key, node->key) > 0)
                swap_nodes(curr, node);
            node = node->next;
        }
        curr = curr->next;
    }
    printf("sort is done \n");
}

void print_sorted_env(t_envp **envp)
{
    t_envp **copy;
    t_envp *current;

    copy = copy_env(envp);
    sort_envp(copy);
    current = *copy;
    while (current)
    {
        printf("declare -x %s", current->key);
        if (current->value)
            printf("=\"%s\"", current->value);
        printf("\n");
        current = current->next;
    }
}

t_envp **copy_env(t_envp **envp)
{
    t_envp **copy;
    t_envp *current;

    current = *envp;
    *copy = NULL;
    while (current)
    {
        env_add(copy, env_create(current->key, current->value));
        current = current->next;
    }
    printf("copy done \n");
    return (copy);
}
int is_key_valid(char *arg, char *pos)
{
    int i;

    i = 0;
    if (!arg || !arg[i])
        return (false);
    if (!(ft_isalpha(arg[i]) || arg[i] == '_'))
        return (false);
    i++;
    while (arg[i] && (arg[i] == '_' || ft_isalnum(arg[i])) && &arg[i] < pos)
        i++;
    if (&arg[i] < pos)
        return (false);
    return (true);
}
void handle_single_export(char *arg, t_envp **envp)
{
    char *key;
    char *value;
    char *pos;
    t_envp *node;

    pos = ft_strchr(arg, '=');
    if (!pos)
        return;
    if (pos == arg || !is_key_valid(arg, pos))
    {
        ft_putstr_fd("export: `", 2);
        ft_putstr_fd(arg, 2);
        ft_putchar_fd('\'', 2);
        return (set_error(": not a valid identifier\n"));
    }
    key = ft_substr(arg, 0, pos - arg);
    value = ft_strdup(pos + 1);
    node = find_node(key);
    if (!node)
        env_add(envp, env_create(key, value));
    else
    {
        free(node->value);
        node->value = ft_str_dup(value);
    }
}

void execute_export(char **args)
{
    t_envp **envp;
    int i;

    envp = get_env_head();
    i = 1;
    if (!args[i])
    {
        print_sorted_env(envp);
        return;
    }
    while (args[i])
    {
        handle_single_export(args[i], envp);
        i++;
    }
}

t_envp *find_node(char *key)
{
    t_envp **envp;
    t_envp *current;

    envp = get_env_head();
    current = *envp;

    while (current)
    {
        if (!ft_strcmp(current->key, key))
            return (current);
        current = current->next;
    }
    return (NULL);
}

void free_env(void *key)
{
    t_envp **envp;
    t_envp *curr;
    t_envp *prev;

    envp = get_env_head();
    if (!envp || !*envp)
        return;
    curr = *envp;
    prev = NULL;
    if (!ft_strcmp(curr->key, key))
    {
        *envp = (*envp)->next;
        free(curr);
        return;
    }
    while (curr)
    {
        if (!ft_strcmp(curr->key, key))
        {
            prev->next = curr->next;
            return (free(curr));
        }
        prev = curr;
        curr = curr->next;
    }
}

void execute_unset(char **args)
{
    t_envp **envp;
    int i;

    envp = get_env_head();
    i = 0;
    while (args[i])
    {
        free_env(args[i]);
        i++;
    }
}

int skip_option(char **arg, int *i)
{
    int check;
    int j;

    check = *i;
    while (arg[*i] && arg[*i][0] == '-')
    {
        j = 1;
        while (arg[*i][j] && arg[*i][j] == 'n')
            j++;
        if (arg[*i][j] == '\0')
        {
            if (arg[*i][j - 1] != 'n')
                return (false);
        }
        else
            return (false);
        (*i)++;
    }
    return (!(check == *i));
}

void execute_echo(char **arg)
{
    int i;
    int option;

    i = 1;
    option = skip_option(arg, &i);
    while (arg[i])
    {
        ft_putstr_fd(arg[i++], STDOUT_FILENO);
        if (arg[i])
            write(1, " ", 1);
    }
    if (!option)
        write(1, "\n", 1);
}
