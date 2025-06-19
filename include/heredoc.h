/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:49:38 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/20 00:15:35 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "ast.h"

# define HDOC_FILE_NAME "/tmp/tmp_heredoc_"
# define HDOC_EXPANDED_PATH "/tmp/heredoc_expanded_path"

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
int			restore_heredoc_offset(int heredoc_fd, char *path);
char		*generate_name(void);
int			expand_heredoc_file(int fd, t_file *file);
void		unlink_heredoc_files(t_ast *ast);

#endif
