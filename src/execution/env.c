#include "../../include/exec.h"

t_envp	**get_env_head(void)
{
	static t_envp	*head;

	return (&head);
}
char **saved_pwd()
{
	static char *pwd;
	return(&pwd);
}
void	get_basics()
{
	char **basics;
	*saved_pwd() = getcwd(NULL,0);

	basics = ft_malloc(sizeof(char *)*5);
	if(!basics)
	{
		set_exec_error("malloc",1);
		return;
	}
	basics[0]=ft_strjoin("PWD=",*saved_pwd());
	basics[2]=ft_strdup("PATH=/app/bin:/usr/bin:/bin");
	basics[1]=ft_strdup("SHLVL=1");
	basics[3]=ft_strdup("_=./minishell");
	basics[4]=NULL;
	execute_export(basics);
	return ;
}
void	get_new_env(t_envp **new_envp, char **old_env)
{
	int		i;
	char	*equal_pos;
	char	*key;
	char	*value;

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
	get_basics();
	return ;
}
