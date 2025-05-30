#include "../../../include/exec.h"

void execute_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        ft_putstr_fd("pwd: error retrieving current directory: ",2);
        set_exec_error("getcwd", 1);
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
