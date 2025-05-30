#include "../../../include/exec.h"

void execute_export(char **args)
{
    t_envp **envp;
    int i;

    envp = get_env_head();
    i = 0;
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

void print_sorted_env(t_envp **envp)
{
    t_envp **copy;
    t_envp *current;

    copy = copy_env(envp);
    if(!*get_error_check())
        return;
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
    free_all_env(copy);
}
