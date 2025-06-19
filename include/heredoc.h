/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:49:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/19 15:50:39 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "ast.h"

# define HEREDOC_PATH "/tmp/heredoc_exp_file"

typedef struct s_heredoc
{
	t_file		**redirect;
	char		*filename;
	char		*eof;
	int			to_expand;
	int			fd;
}				t_heredoc;

void		heredoc_handler(char *eof, t_file **redirect);
void		heredoc(t_heredoc *hd);
void		heredoc_error(char *nb_line, char *lim);
char		*heredoc_expander(char *s);
int			restore_heredoc_offset(int heredoc_fd);

#endif
