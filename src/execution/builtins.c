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
    if (!ft_strcmp(cmd, "exit"))
        return (EXIT);
    return (-1);
}
int execute_builtins(builtin_type type, char **args)
{
    if(type == ECHO)
        return (execute_echo(args));
    if(type == CD)
        return(execute_cd(*args));
    if(type == PWD)
        return(execute_pwd());
    if(type == EXPORT)
        return(execute_export(args));
    if(type == UNSET)
        return (execute_unset(args));
    if(type == ENV)
        return(execute_env());
    if(type == EXIT)
        return (execute_exit());                                                                                                                                                                    
}

int execute_cd(char *args)
{
    t_envp **envp;
    char *old_pwd;
    char *new_pwd;

    envp = get_env_head();
    old_pwd = getcwd(NULL,0);
    if( !args || chdir(args) != 0)
    {
        perror("cd: "); 
        free(old_pwd);
        return (1);
    }
    new_pwd = getcwd(NULL,0);
    execute_export(ft_strjoin("PWD=",new_pwd));
    execute_export(ft_strjoin("OLDPWD=",old_pwd));
    free(new_pwd);
    return(0);
}

int execute_pwd()
{
    char *cwd;

    cwd = getcwd(NULL,0);
    if(!cwd)
    {
        perror("getcwd error");
        return (-1);
    }
    printf("%s\n",cwd);
    free(cwd);
    return (0);  
}
int execute_env()
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
    return (0);
}
int execute_export(char *args)
{
    
}