/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/03 13:57:15 by hfegrach         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "gc.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "lexer.h"
# include "expander.h"

void    handler_SIGINT(int sig);
void	sigint_handler(int sig);
#endif