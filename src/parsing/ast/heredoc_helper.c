/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/11 20:32:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"
#include "../../../include/heredoc.h"

char	*generate_name(void)
{
	char	*name;
	char	*tmp;
	int		i;

	tmp = ft_strdup("/tmp/tmp_heredoc_");
	i = 0;
	name = ft_strjoin(tmp, ft_itoa(i));
	while (!access(name, F_OK))
		name = ft_strjoin(tmp, ft_itoa(++i));
	return (name);
}

t_heredoc	*init_heredoc(char *eof)
{
	t_heredoc	*hd;

	hd = gc_alloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->eof = remove_quotes(eof);
	hd->filename = generate_name();
	hd->to_expand = !(is_quoted(eof));
	hd->lim = ft_strjoin(hd->eof, "\n");
	hd->fd = open(hd->filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!hd->fd)
		perror("failed to open");
	return (hd);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	clean_and_exit(NULL, 130);
}

void	heredoc_error(char *nb_line, char *lim)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}
