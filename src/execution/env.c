#include "../../include/exec.h"

t_envp *env_create(char *key, char *value)
{
	t_envp *new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->key = ft_str_dup(key);
	if (value)
		new->value = ft_str_dup(value);
	new->next = NULL;
	return (new);
}

void env_add(t_envp **envp, t_envp *new)
{
	if (!envp || !new)
		return;
	if (!(*envp))
	{
		*envp = new;
		return;
	}
	(get_env_last(*envp))->next = new;
}

t_envp *get_env_last(t_envp *env)
{
	t_envp *current;

	current = env;
	while (current && current->next)
		current = current->next;
	return (current);
}

void get_basics(t_envp **new_envp)
{
	char *cwd = getcwd(NULL, 0);

	env_add(new_envp, env_create("PATH", "/bin:/usr/bin"));
	env_add(new_envp, env_create("PWD", cwd));
	// env_add(new_envp, env_create("SHLVL", "1"));
	// env_add(new_envp, env_create("_", "/usr/bin/env"));
	env_add(new_envp, env_create("OLDPWD", NULL));
	free(cwd);
	return;
}
void get_new_env(t_envp **new_envp, char **old_env)
{
	int i;
	char *equal_pos;
	char *key;
	char *value;

	if (!old_env || !*old_env)
	{
		get_basics(new_envp);
		return ;
	}
	i = 0;
	while (old_env[i])
	{
		equal_pos = ft_strchr(old_env[i], '=');
		key = ft_sub_str(old_env[i], 0, equal_pos - old_env[i]);
		value = ft_str_dup(equal_pos + 1);
		env_add(new_envp, env_create(key, value));
		i++;
		free(key);
		free(value);
	}
		return ;
}

void print_env(t_envp **env)
{
	t_envp *current;
	current = *env;

	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

t_envp **get_env_head()
{
	static t_envp *head;

	return (&head);
}
void free_all_env(t_envp **envp)
{	
	t_envp *current;
	current = *envp;

	while(*envp)
	{
		if((*envp)->key)
			free((*envp)->key);
		if((*envp)->value)
			free((*envp)->value);
		current = *envp;
		*envp = (*envp)->next;
		free(current);
	}

}
// char *ft_getenv(char *key)
// {
// 	t_envp *current;

// 	current = *get_env_head();
// 	while (current)
// 	{
// 	    if (ft_strcmp(current->key, key) == 0)
// 	        return (current->value);
// 	    current = current->next;
// 	}
// 	return (NULL);
// }