#include "../include/minishell.h"

const char *prompt(void)
{
	return ("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_token *token;
	t_ast *ast;

	(void)ac;
	(void)av;
	(void)envp;
	token = NULL;
	while (1)
	{
		line = readline(prompt());
		if (!line)
			break;
		token = tokenizer(line);
		ast = parser(&token);
		ast_print(ast);
		*get_parser_check() = true;
		finish(line);
		free_all();
	}
	return (0);
}

void finish(char *line)
{
	add_history(line);
	free(line);
}
