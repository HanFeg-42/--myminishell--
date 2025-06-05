/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:22 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/04 20:21:19 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/minishell.h"

const char	*prompt(void)
{
	return ("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
}

void handler_SIGINT(int sig)
{
    (void)sig;
	write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	*get_status_code() = 130;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_ast	*ast;

	(void)ac;
	(void)av;
	signal(SIGINT, handler_SIGINT);
	signal(SIGQUIT, SIG_IGN);
	get_new_env(get_env_head(), envp);
	while (1)
	{
		line = readline(prompt());
		if (!line)
			break ;
		token = tokenizer(line);
		ast = parser(&token);
		*get_error_check() = true;
		execute_compound(ast);
		finish(line);
		free_all();
		signal(SIGINT, handler_SIGINT);
	}
	ft_putendl_fd("exit", 1);
	if (*saved_pwd())
		free(*saved_pwd());
	free_all_env(get_env_head());
	free_all();
	return (*get_status_code());
}

void	finish(char *line)
{
	*get_parser_check() = true;
	*get_heredoc_check() = true;
	add_history(line);
	free(line);
}
