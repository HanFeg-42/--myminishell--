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
t_heredoc	*heredoc_init(char *eof);
void		heredoc(t_heredoc *hd);
int	*get_heredoc_check(void);
void	heredoc_error(char *nb_line, char *lim);

#endif
