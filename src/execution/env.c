#include "../../include/exec.h"

t_envp	*env_create(char *key, char *value)
{
	t_envp	*new;

	new = ft_malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	env_add(t_envp **envp, t_envp *new)
{
    if (!envp || !new)
    return ;
    if (!(*envp))
    {
        *envp = new;
        return ;
	}
	(get_env_last(*envp))->next = new;
}

t_envp	*get_env_last(t_envp *env)
{
	t_envp	*current;

	current = env;
	while (current && current->next)
		current = current->next;
	return (current);
}

t_envp	*get_new_env(char **old_env)
{
	int		i;
	t_envp	*new_envp;
	char	*equal_pos;
    char *key;
    char *value;

    new_envp = NULL;
	i = 0;
	while (old_env[i])
	{
		equal_pos = ft_strchr(old_env[i], '=');
        key = ft_substr(old_env[i],0,equal_pos-old_env[i]);
        value = ft_strdup(equal_pos + 1);
		env_add(&new_envp, env_create(key,value));
		i++;
	}
	return (new_envp);
}

void	print_env(t_envp *env)
{
	t_envp *current;
	current = env;

	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}