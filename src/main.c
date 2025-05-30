#include "../include/minishell.h"
#include "../include/exec.h"

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
	signal(SIGINT, SIG_IGN);
    get_new_env(get_env_head(),envp);
	token = NULL;
	while (1)
	{
		line = readline(prompt());
		if (!line)
			break;
		token = tokenizer(line);
		ast = parser(&token);
		*get_error_check() = true;
		execute_compoud(ast);
		*get_parser_check() = true;
		finish(line);
		free_all();
	}
	free_all_env(get_env_head());
	return (0);
}

void finish(char *line)
{
	add_history(line);
	free(line);
}
