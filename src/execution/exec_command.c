#include "../../include/exec.h"
int	has_output_redirection(t_file *redirect)
{
    t_file *current;

    current = redirect;
    while (current)
    {
        if (current->type == OUTPUT_RED || current->type == APPEND)
            return (1);
        current = current->next;
    }
    return (0);
}
int	has_input_redirection(t_file *redirect)
{
	t_file	*current;

	current = redirect;
	while (current)
	{
		if (current->type == INPUT_RED)
			return (1);
		current = current->next;
	}
	return (0);
}
void execute_command(t_ast *ast, t_pipe *pipeline, int i)
{
    t_ast *current;

    current = ast->first_child;
    if (current->type == AST_SIMPLE_CMD)
    {
        execute_simple_cmd(current, pipeline, i);
    }
    else
        execute_subshell(current, pipeline);
}