#ifndef HEREDOC_H
# define HEREDOC_H

# include "ast.h"

typedef struct s_heredoc
{
	char		*lim;
	int			to_expand;
	int			fd;
	char		*filename;
	char		*eof;
	t_file		**redirect;
}               t_heredoc;

char		*generate_name(void);
void    	heredoc_handler(char *eof, t_file **redirect);
t_heredoc	*init_heredoc(char *eof);
void		heredoc2(t_heredoc *hd);
int	*get_heredoc_check(void);

#endif
