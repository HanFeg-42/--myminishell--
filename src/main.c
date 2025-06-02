/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:22 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/02 17:40:43 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/minishell.h"

const char	*prompt(void)
{
	return ("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_ast	*ast;

	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	get_new_env(get_env_head(), envp);
	// token = NULL;
	while (1)
	{
		line = readline(prompt());
		if (!line)
			break ;
		token = tokenizer(line);
		ast = parser(&token);
		*get_error_check() = true;
		execute_compoud(ast);
		execute_compound(ast);
		*get_parser_check() = true;
		finish(line);
		free_all();
	}
	free_all_env(get_env_head());
	return (0);
}

void	finish(char *line)
{
	*get_parser_check() = true;
	*get_heredoc_check() = true;
	add_history(line);
	free(line);
}
