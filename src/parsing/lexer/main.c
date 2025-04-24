#include "../../../include/minishell.h"

int main()
{
	char *line;
	t_token *token;
	
	token = NULL;
	while (1)
	{
		line = readline("\033[38;2;255;105;180mMinishell > \033[0m");
		if (!line)
		break;
		token = tokenizer(line);
		*get_parser_check() = true;
		token_print(token);
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
