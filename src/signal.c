/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:22 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/15 17:13:39 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/minishell.h"

void	sigint_handler_in_main(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*get_status_code() = 130;
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sigint_handler_in_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	clean_and_exit(130);
}
