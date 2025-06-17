/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/17 14:45:00 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "gc.h"
# include "lexer.h"
# include "expander.h"

void	sigint_handler_in_main(int sig);
void	sigint_handler_in_heredoc(int sig);
void	reset_checker_state(void);
void	setup_signals(void);
void	ignore_signals(void);
int		*get_heredoc_check(void);
size_t	*get_arg_size(void);

#endif