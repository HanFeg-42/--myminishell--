#include "../../../include/ast.h"

t_ast   *compound(t_token *tokens)
{
    t_ast *ast_head;
    t_ast *pipeline;
    int type;

    ast_head = ast_create(AST_COMPOUND);
    if (!ast_head)
        return (NULL);
    while (1)
    {
        pipeline = pipeline(&tokens);
        if (!pipeline)
            return (syntax_error());
        ast_add(ast_head,pipeline);
        type = check_and_or_token(tokens);
        if (type < 0)
            break;
        ast_add(&ast_head, ast_create(type));
        token_advance(&tokens);
    }
    return (ast_head);
}

t_ast *pipeline(t_token *tokens)
{
    t_ast *pipeline;
    t_ast *command;

    pipeline = ast_create(AST_PIPELINE);
    if (!pipeline)
        return (NULL);
    while (1)
    {
        command = command(&tokens);
        if (!command)
            return (syntax_error());
        ast_add(pipeline, command);
        if (!tokens || tokens->type != PIPE)
            break ;
        token_advance(&tokens);
    }
    return (pipeline);
}

t_ast *command(t_token *tokens)
{
    t_ast *command;
    t_ast *result;

    command = ast_create(AST_COMMANDD);
    if (!command)
        return (NULL);
    if (tokens->type == OPAREN)
    {
        token_advance(&tokens);
        result = subshell(tokens);
    }
    else
        result = simple_command(tokens);
    if (!result)
        return (syntax_error());
    ast_add(command, result);
    return (command);
}

t_ast *simple_command(t_token *tokens)
{
    
}
