
#include "../../libft/libft.h"


int main(int ac , char **av)
{
    char *pos;
    char *key;
    char *value;

    pos = ft_strchr(*av, '=');
    if (!pos)
        {
            printf("mockellaaa\n");
        }
    key = ft_substr(*av, 0, pos - (*av));
    value = ft_strdup(pos + 1);

    
}