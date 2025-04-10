#include "../include/minishell.h"

void	parser(t_token *tok)
{
	parse_quotes(tok);
}

void	parse_quotes(t_token *tok)
{
	parse_dquote(tok, DQUOTE);
	parse_dquote(tok, SQUOTE);
	// int	d_stat;
	// int	s_stat;

	// d_stat = 1;
	// s_stat = 1;
	// if (!(*get_parser_check()))
	// 	return ;
	// while (tok)
	// {
	// 	if (tok->type == DQUOTE && d_stat && s_stat)
	// 		d_stat = 0;
	// 	else if (tok->type == DQUOTE && !d_stat)
	// 		d_stat = 1;
	// 	if (tok->type == SQUOTE && s_stat && d_stat)
	// 		s_stat = 0;
	// 	else if (tok->type == SQUOTE && !s_stat)
	// 		s_stat = 1;
	// 	tok = tok->next;
	// }
	// if (!d_stat || !s_stat)
	// {
	// 	throw_error("unclosed quotes");
	// 	*get_parser_check() = false;
	// }
}

void	parse_dquote(t_token *tok, t_token_type quote)
{
	int	q_stat;

	q_stat = 1;
	if (!(*get_parser_check()))
		return ;
	while (tok)
	{
		// printf("hi");
		if (tok->type == quote && q_stat)
			q_stat = 0;
		else if (tok->type == quote && !q_stat)
			q_stat = 1;
		tok = tok->next;
	}
	if (!q_stat)
	{
		throw_error("unclosed quotes");
		*get_parser_check() = false;
	}
}
