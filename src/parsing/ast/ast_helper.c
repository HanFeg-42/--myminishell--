#include "../../../include/ast.h"

t_ast *ast_create(ast_type type)
{
    t_ast *new;

    new = ft_malloc(sizeof(t_ast));
    if (!new)
        return (NULL);
    new->type = type;
    new->first_child = NULL;
    new->next_sibling = NULL;
    new->args = NULL;
    new->i = 0;
    new->redirect = NULL;
    return (new);
}

void ast_add(t_ast *head, t_ast *child)
{
    t_ast *last;

    if (!head || !child)
        return ;
    if (head->first_child == NULL)
    {
        head->first_child = child;
        return ;
    }
    last = ast_last(head->first_child);
    last->next_sibling = child;
}

t_ast	*ast_last(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast)
	{
		if (ast->next_sibling == NULL)
			break ;
		ast = ast->next_sibling;
	}
	return (ast);
}

void token_advance(t_token **token)
{
    if (!token || !(*token))
        return ;
    *token = (*token)->next;
}


