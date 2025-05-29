#include "../../../include/exec.h"

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