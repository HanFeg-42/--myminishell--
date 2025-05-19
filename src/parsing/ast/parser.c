#include "../../../include/ast.h"

t_ast *parser(t_token **token)
{
    t_ast *ast;

    if (!(*get_parser_check()) || !(*token))
        return (NULL);
    ast = ast_compound(token);
    if (!ast)
    {
        if (!(*get_heredoc_check()))
            return(NULL);
        if ((*token))
            syntax_error((*token)->value);
        else
            syntax_error("newline"); // zoidiha as a token f tokenization
    }
    else if (*(token))
    {
        syntax_error((*token)->prev->value);
        return (NULL);
    }
    return (ast);
}

void ast_print(t_ast *ast)
{
    if (!ast)
        return ;
    printf("type : %d\t", ast->type);
    print_args(ast->args);
    print_redirect(ast->redirect);
    ast_print(ast->first_child);
    // printf("|\n");
    ast_print(ast->next_sibling);
}

void print_args(char **args)
{
    int i;

    if (!args)
        return ;
    printf("args:");
    i = 0;
    while (args[i])
    {
        printf("%s; ", args[i]);
        i++;
    }
    printf("\n");
    expander(args);
}

void print_redirect(t_file *redirect)
{
    if (!redirect)
        return ;
    printf("files:");
    while (redirect)
    {
        printf("%s; ", redirect->filename);
        redirect = redirect->next;
    }
}
