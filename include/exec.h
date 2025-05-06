#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
// #include "minishell.h"

typedef struct s_envp	t_envp;

struct					s_envp
{
	char				*key;
	char				*value;
	t_envp				*next;
};

t_envp	*env_create(char *key, char *value);
void	env_add(t_envp **envp, t_envp *new);
t_envp	*get_env_last(t_envp *env);
t_envp	*get_new_env(char **old_env);
void print_env(t_envp *env);

#endif