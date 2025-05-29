#include "../../../include/exec.h"


void execute_cd(char **args)
{
    char *old_pwd;
    char *new_pwd;
    char *path;

    if (!args[1])
    {
        path = ft_getenv("HOME");
        if (!path)
            return (set_error("cd: HOME not set\n"));
    }
    else if (args[2])
        return (set_error("cd: too many arguments\n"));
    else
        path = args[1];
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
        return (set_exec_error("getcwd error", 1));
    if (!args || chdir(path) != 0)
        return (free(old_pwd), set_exec_error("cd", 1));
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
        return (set_exec_error("getcwd error", 1));
    update_env(old_pwd, new_pwd);
}

void update_env(char *old_pwd, char *new_pwd)
{
    char **elems;

    elems = ft_malloc(sizeof(char *) * 3);
    if (!elems)
    {
        set_exec_error("malloc faillure :", 1);
        free(new_pwd);
        free(old_pwd);
        return;
    }
    elems[0] = ft_strjoin("PWD=", new_pwd);
    elems[1] = ft_strjoin("OLDPWD=", old_pwd);
    elems[2] = NULL;
    execute_export(elems);
}

void set_error(char *str)
{
    if (str)
        ft_putstr_fd(str, 2);
    set_exec_error(NULL, 1);
}
