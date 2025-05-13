#include "../../../include/expander.h"

char    **expander(char **args)
{
    t_expand *expand;
    char **arg;

    expand = init_expand(args);
    while (expand->args[expand->i]) // example : { echo; $hi; NULL }
    {
        expand_param(expand); //looks for $ dquoted or unquoted then replace it
        field_split(expand); // split nodes value by IFS (tab or space) outside quotes
        expand_pathname(expand); // look for * the replace it with correspond files + split it in parallel and add to (include field split)
        expand_advance(expand); // inncrement i
    }
    arg = remove_quotes_from_all(expand);
    return(arg);
}

t_expand *init_expand(char **args)
{
    t_expand *exp;

    exp = ft_malloc(sizeof(t_expand));
    if (!exp)
        return (NULL);
    exp->arg = NULL;
    exp->args = args;// alloci a zmer
    exp->i = 0;
    exp->stat = 0;
    exp->pos = 0;
    return (exp);
}

void    expand_param(t_expand *exp)
{
    char *word;

    word = exp->args[exp->i];
    exp->word = ft_strdup("");
    while (word[exp->pos])
    { // red lbal l sigle quote & double quote
        if (word[exp->pos] == 34 && exp->stat == 0)
        {
            // inside double quotes
            expand_inside_double_quote(exp);
        }
        else if ((word[exp->pos] == 34 && exp->stat == 1) || (word[exp->pos] == 39 && exp->stat == 2))
        {
            // outside quotes
            exp->stat = 0;
            expand_unquote(exp);
        }
        else if (word[exp->pos] == 39 && exp->stat == 0)
        {
            // inside single quotes
            copy_characters_until_quote(exp);
        }
    }
}

void copy_characters_until_quote(t_expand *exp)
{
    // ana hna : exp->args[exp->i] + exp->pos = 39
    char *curr_pos;
    char *sq_pos;

    exp->stat = 2;
    curr_pos = exp->args[exp->i] + exp->pos;
    sq_pos = ft_strchr(curr_pos + 1, 39);
    exp->word = ft_strjoin(exp->word, ft_substr(curr_pos, 0, sq_pos - curr_pos));
    exp->pos += sq_pos - curr_pos;
}

void    expand_inside_double_quote(t_expand *exp)
{
    char *dq_pos;
    char *curr_pos;
    char    *dollar_pos;

    exp->stat = 1;
    curr_pos = exp->args[exp->i] + exp->pos;
    dq_pos = ft_strchr(curr_pos + 1, 34);
    while(*curr_pos && curr_pos < dq_pos)
    {
        dollar_pos = ft_strnchr(curr_pos, '$', dq_pos - curr_pos);
        if (!dollar_pos)
        {
            exp->word = ft_strjoin(exp->word, curr_pos); // need new strjoin that returns s1 if !s2
            break;
        }
        exp->word = ft_strjoin(exp->word, ft_substr(curr_pos, 0, dollar_pos - curr_pos)); // need new substr that start always = 0
        exp->word = ft_strjoin(exp->word, get_env_name(dollar_pos));
        curr_pos = skip_env_var(dollar_pos + 1);
    }
    exp->pos += dq_pos - curr_pos;
}

//TODO : expand_param(t_expand *expand)
//TODO : field_split(t_expand *expand)
//TODO : expand_path(t_expand *expand)
//TODO : expand_advance(t_expand *expand)
//TODO : remove_quotes_from_all(t_expand *expand)
//TODO : expand_inside_double_quote(exp)
//TODO : copy_characters_until_quote(exp)
//TODO : expand_inside_single_quote(exp)