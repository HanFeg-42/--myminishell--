#include "../../../include/ast.h"

void parser(t_token **token)
{
    t_ast *ast;
    ast = ast_compound(token);
    if (!ast)
        syntax_error((*token)->value);
}
