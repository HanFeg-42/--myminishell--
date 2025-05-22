#include "../include/minishell.h"
void handler_SIGINT(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0); // hadi kima glt ma3ndha tachi dawr flhayat
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_token *token;
	t_ast *ast;

	signal(SIGINT, handler_SIGINT);
	// signal(SIGINT, SIG_IGN);
	(void)ac;
	(void)av;
	(void)envp;
    // get_new_env(get_env_head(),envp);
	//print_env(get_env_head());
	token = NULL;
	while (1)
	{
		line = readline("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
		if (!line)
			break;
		token = tokenizer(line);
		ast = parser(&token);
		(void)ast;
		ast_print(ast);
		*get_parser_check() = true;
		finish(line);
		free_all();
	}
	return (0);
}

void finish(char *line)
{
	printf("\n");
	add_history(line);
	free(line);
}
