/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:18 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/15 11:20:19 by hfegrach         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "gc.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// " => 34
// ' => 39

# include "lexer.h"
# include "./ast.h"
// # include "exec.h"
# include "expander.h"
#endif