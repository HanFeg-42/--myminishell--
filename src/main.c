#include "../include/minishell.h"

int main()
{
	char *line;
	t_token *token;
	t_ast *ast;
	
	token = NULL;
	while (1)
	{
		line = readline("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
		if (!line)
		break;
		token = tokenizer(line);
		// token_print(token);
		ast = parser(&token);
		ast_print(ast);
		*get_parser_check() = true;
		finish(line);
	}
	return (0);
}

void finish(char *line)
{
	printf("\n");
	add_history(line);
	free(line);
	free_all();
}
