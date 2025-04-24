#include "../../../include/minishell.h"

void throw_error(char *err)
{
    printf("%s\n", err); //katrprinti l error
    rl_replace_line("", 0); // ila knt deja katba chi haja kat7ydha
    rl_on_new_line(); // kat3yt l readline 3awtani walakin makat affichiha ta kanpressi chi key
    // rl_redisplay(); // hai kataffichi lia dek lmsg li 3atya l readline once the signal ddar
	*get_parser_check() = false;

}

void lexer_throw_error(t_lexer *lexer, char *err)
{
    throw_error(err);
    while (lexer->c)
        lexer_advance(lexer);
}
