#ifndef EXPANDER_H
# define EXPANDER_H

# include "ast.h"

typedef struct s_arg
{
    char *value;
    struct s_arg *next;
}               t_arg;

typedef struct s_expand
{
    t_arg *arg;
    char **args;
    char *word;
    int i;
    int stat;
    int pos;
}               t_expand;

#endif