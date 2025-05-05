#include "../../../include/ast.h"

void    heredoc(char *eof, t_file **redirect)
{
    char *lim;
    int to_expand;
    int fd;
    char *line;

    if (is_quoted(eof))
        to_expand = false;
    else
        to_expand = true;
    lim = quote_removal(eof);
    fd = open("filename", O_CREAT | O_RDWR , 0777);
    line = get_next_line(0);
    while (line && ft_strncmp(line, lim, ft_strlen(lim))) // limmmmm == lim
    {
        if (to_expand)
            line = heredoc_expander(line);
        write(fd, line, ft_strlen(line));
        free_one(line);
        line = get_next_line(0);
    }
    free_one(line);
    close(fd);
    redirect_add(redirect,
        redirect_create(HERE_DOC, "filename"));
    return ;
}

int is_quoted(char *eof)
{
    if (ft_strchr(eof, 34) || ft_strchr(eof, 39))
        return (true);
    return (false);
}

char *quote_removal(char *str)
{
    int stat;
    int i;
    int j;
    char *ret;

    ret = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!ret)
        return (NULL);
    stat = 0;
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 34 && stat == 0) // inside double quotes
            stat = 1;
        else if (str[i] == 34 && stat == 1) // khrjt mn l quoted stat + now on normal stat 
            stat = 0;
        else if (str[i] == 39 && stat == 0) // inside single quotes
            stat = 2;
        else if (str[i] == 39 && stat == 2) // khrjt mn l quoted stat + now on normal stat 
            stat = 0;
        else
            ret[j++] = str[i];
        i++;
    }
    ret[j] = '\0';
    return (ret);
}

//TODO:======================= is_quoted --> DONE
//TODO:======================= quote_removal
//TODO:======================= heredoc_expander