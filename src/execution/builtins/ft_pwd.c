#include "../../../include/exec.h"

void execute_pwd()
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        cwd = ft_str_dup(*saved_pwd());
    }
    printf("%s\n", cwd);
    free(cwd);
}
