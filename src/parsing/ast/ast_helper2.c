#include "../../../include/ast.h"

t_file *redirect_create(int type, char *filename)

{
    t_file *redirect_file;

    redirect_file = ft_malloc(sizeof(t_file));
    if (!redirect_file)
        return (NULL);
    redirect_file->filename = ft_strdup(filename);
    redirect_file->type = type;
    redirect_file->next = NULL;
    return (redirect_file);
}

void redirect_add(t_file **redirect, t_file *new)
{
    t_file *current;

    if(!redirect || !new)
        return;
    if(!(*redirect))
        *redirect = new;
    else
    {
        current = (*redirect);
        while(current->next)
            current = current ->next;
        current->next = new;
    }
}

int is_token_redirect(t_token *token)
{
    if (!token)
        return (0);
    if (token->type == INPUT_RED
        || token->type == OUTPUT_RED
        || token->type == APPEND
        || token->type == HERE_DOC)
        return (1);
    return (0);
}

void add_args(t_token **token, t_ast *simple_cmd)
{
    if (!simple_cmd->args)
    {
        simple_cmd->args = ft_realloc(simple_cmd->args, sizeof(char *) * (simple_cmd->i + 2));
        if (!simple_cmd->args)
            return ;
    }
    simple_cmd->args[simple_cmd->i++] = ft_strdup((*token)->value);
    simple_cmd->args[simple_cmd->i] = NULL;
    token_advance(token);
}

void *ft_realloc(void *ptr, size_t size)
{
    void *new_ptr;

    new_ptr = ft_malloc(size);
    if (!new_ptr)
        return (NULL);
    copy_ptr(ptr, new_ptr);
    free_old_ptr(ptr);
    return (new_ptr);
}

void *syntax_error(char *err)
{
    *(get_parser_check()) = false;
    if (err)
    {
        ft_putstr_fd("syntax error near unexpected token ", 2);
        ft_putstr_fd(err, 2);
    }
    return (NULL);
}

void heredoc(char *delim)
{
    (void)delim;
    return ;
}

int is_empty_cmd(t_ast *simple_cmd)
{
    if (!simple_cmd->args && !simple_cmd->redirect)
        return (true);
    return (false);
}

int check_and_or_token(t_token *token)
{
    if (!token)
        return (-1);
    if (token->type == AND)
        return (AST_AND);
    else if (token->type == OR)
        return (AST_OR);
    return (-1);
}