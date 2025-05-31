#include "../../../include/exec.h"

void execute_cd(char **args)
{
    char *old_pwd;
    char *new_pwd;
    char    *path;

    if (!args[0] || !ft_strcmp(args[0], "~"))
    {
        path = ft_getenv("HOME");
        if (!path)
            return (set_error("cd: HOME not set\n"));
    }
    else if (args[1])
        return (set_error("cd: too many arguments\n"));
    else
        path = args[0];
    old_pwd = getcwd(NULL, 0);
    if (chdir(path) != 0 || !old_pwd)
    {
        return (free(old_pwd), ft_putstr_fd("cd: ", 2), ft_putstr_fd(path, 2), set_exec_error(" ", 1));
    }
    new_pwd = getcwd(NULL, 0);
    update_env(old_pwd, new_pwd);
}

void update_env(char *old_pwd, char *new_pwd)
{
    char **elems;

    elems = ft_malloc(sizeof(char *) * 3);
    if (!elems)
    {
        set_exec_error("malloc:", 1);
        if (new_pwd)
            free(new_pwd);
        if (old_pwd)
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
