#include "../../../include/exec.h"


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
t_envp **copy_env(t_envp **envp)
{
    t_envp **copy;
    t_envp *current;

    current = *envp;
    copy=malloc(sizeof(t_envp));
    if(!copy)
    {
        set_exec_error("malloc",1);
        return(NULL);
    }
    *copy = NULL;
    while (current)
    {
        env_add(copy, env_create(current->key, current->value));
        current = current->next;
    }
    return (copy);
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
}