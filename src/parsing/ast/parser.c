#include "../../../include/ast.h"
// #include "../../../include/minishell.h"

t_ast *parser(t_token **token)
{
    t_ast *ast;
    
    ast = ast_compound(token);
    if (!ast)
        syntax_error((*token)->value);
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
    printf("|\n");
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