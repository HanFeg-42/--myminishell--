#include "../include/minishell.h"

void	parser(t_token *tok)
{
	parse_quotes(tok);
	parse_parentheses(tok);
}

void	parse_quotes(t_token *tok)
{
	int	d_stat;
	int	s_stat;

	d_stat = 1;
	s_stat = 1;
	if (!(*get_parser_check()))
		return ;
	while (tok)
	{
		if (tok->type == DQUOTE && d_stat && s_stat)
			d_stat = 0;
		else if (tok->type == DQUOTE && !d_stat)
			d_stat = 1;
		if (tok->type == SQUOTE && s_stat && d_stat)
			s_stat = 0;
		else if (tok->type == SQUOTE && !s_stat)
			s_stat = 1;
		tok = tok->next;
	}
	if (!d_stat || !s_stat)
		throw_error("unclosed quotes");
}
void	parse_parentheses(t_token *tok)
{
	int check;
	int p_count;

	if (!(*get_parser_check()))
		return ;
	check = 0;
	p_count = 0;
	while (tok)
	{
		if (tok->type == CPAREN && p_count <= 0)
		{
			check = 1;
			break;
		}
		if (tok->type == OPAREN)
			p_count++;
		if (tok->type == CPAREN)
			p_count--;
		tok = tok->next;
	}
	if (check || p_count)
		throw_error("unclosed parentheses");
}
