#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	t_token *token;
	t_ast *ast;

	(void)ac;
	(void)av;
    get_new_env(get_env_head(),envp);
	
	print_env(get_env_head());
	// token = NULL;
	// while (1)
	// {
	// 	line = readline("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
	// 	if (!line)
	// 		break;
	// 	token = tokenizer(line);
	// 	ast = parser(&token);
	// 	ast_print(ast);
	// 	*get_parser_check() = true;
	// 	finish(line);
	// }
	// free_all();
	// return (0);
}

void finish(char *line)
{
	printf("\n");
	add_history(line);
	free(line);
}
