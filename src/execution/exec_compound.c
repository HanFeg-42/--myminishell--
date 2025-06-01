#include "../../include/exec.h"

int	*get_status_code(void)
{
	static int	status = 0;

	return (&status);
}

void	ast_advance(t_ast **current)
{
	if (*current)
		*current = (*current)->next_sibling;
}

void	and_or_handler(t_ast *current)
{
	if (current->type == AST_OR)
	{
		ast_advance(&current);
		if (!(*get_status_code()))
		{
			while (current && current->type != AST_AND)
				ast_advance(&current);
		}
	}
	if (current && current->type == AST_AND)
	{
		ast_advance(&current);
		if (current && *get_status_code())
			ast_advance(&current);
	}
}

void	execute_compoud(t_ast *ast)
{
	t_ast	*current;

	if (!ast || !(*get_parser_check()))
		return ;
	current = ast->first_child;
	while (current)
	{
		execute_pipeline(current);
		ast_advance(&current);
		if (current)
		{
			if (current->type == AST_OR)
			{
				ast_advance(&current);
				if (!(*get_status_code()))
				{
					while (current && current->type != AST_AND)
						ast_advance(&current);
				}
			}
			if (current && current->type == AST_AND)
			{
				ast_advance(&current);
				if (current && *get_status_code())
					ast_advance(&current);
			}
			// and_or_handler(current);
		}
		else
			break ;
	}
}
