/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:22 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/19 23:24:48 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/minishell.h"

static const char	*get_prompt(void)
{
	return ("\001\033[38;2;255;105;180m\002Minishell > \001\033[0m\002");
}

static void	init_shell(int ac, char **av, char **envp)
{
	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd("Too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, sigint_handler_in_main);
	signal(SIGQUIT, SIG_IGN);
	get_new_env(get_env_head(), envp);
}

static void	clean_cmd_resources(char *line)
{
	reset_checker_state();
	add_history(line);
	free(line);
	free_all();
	signal(SIGINT, sigint_handler_in_main);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*token;
	t_ast	*ast;

	init_shell(ac, av, envp);
	while (true)
	{
		line = readline(get_prompt());
		if (!line)
			break ;
		token = tokenizer(line);
		ast = parser(&token);
		execute_compound(ast);
		clean_cmd_resources(line);
	}
	ft_putendl_fd("exit", 1);
	clean_and_exit(*get_status_code());
}
