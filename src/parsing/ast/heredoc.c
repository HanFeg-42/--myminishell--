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
    line = get_next_line(0, 0);
    while (line && !ft_strncmp(line, lim, ft_strlen(lim))) // limmmmm == lim
    {
        if (to_expand)
            line = heredoc_expander(line);
        write(fd, line, ft_strlen(line));
        free_one(line);
        line = get_next_line(0, 0);
    }
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
    char *ret;

    ret = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!ret)
        return (NULL);
    //need a good algo
    return (ret);
}

//TODO:======================= is_quoted
//TODO:======================= quote_removal
//TODO:======================= heredoc_expander