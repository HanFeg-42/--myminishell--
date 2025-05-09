#ifndef EXEC_H
#define EXEC_H

#include "ast.h"
// #include "minishell.h"

typedef struct s_envp t_envp;

struct s_envp
{
	char *key;
	char *value;
	t_envp *next;
};
enum s_builtin_type 
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};
typedef enum s_builtin_type builtin_type;

t_envp *env_create(char *key, char *value);
void env_add(t_envp **envp, t_envp *new);
t_envp *get_env_last(t_envp *env);
void get_new_env(t_envp **new_envp, char **old_env);
void print_env(t_envp **env);
t_envp **get_env_head(void);
#endif