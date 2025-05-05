#include "../../../include/ast.h"

char    *heredoc_expander(char *s)
{
    char    *ret;
    char    *dollar_pos;

    if (!s)
        return (NULL);
    ret = ft_strdup("");
    while(*s)
    {
        dollar_pos = ft_strchr(s, '$');
        if (!dollar_pos)
        {
            ret = ft_strjoin(ret, s); // need new strjoin that returns s1 if !s2
            break;
        }
        ret = ft_strjoin(ret, ft_substr(s, 0, dollar_pos - s)); // need new substr that start always = 0
        s = skip_env_var(dollar_pos + 1);
    }
    return (ret);
}

char    *get_env_name(char *s)
{
    char    *var;
    int i;

    i = 1;
    while (s[i] && ft_isalnum(s[i]))
        i++;
    var = ft_substr(s, 1, i - 1);
    return (ft_getenv(var));
}

char    *skip_env_var(char *s)
{
    while (*s && ft_isalnum(*s))
        s++;
    return (s);
}

char    *ft_getenv(char *var)
{
    return (getenv(var));
}
