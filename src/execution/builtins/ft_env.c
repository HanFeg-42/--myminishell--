#include "../../../include/exec.h"


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