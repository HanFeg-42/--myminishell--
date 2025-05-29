#include "../../../include/exec.h"

void execute_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        set_exec_error("getcwd error", 1);
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
}
