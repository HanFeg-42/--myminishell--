/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/03 15:26:01 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"
#include "../../../include/heredoc.h"

void	heredoc_handler(char *eof, t_file **redirect)
{
	t_heredoc	*hd;
	pid_t		pid;
	int			status;

	hd = init_heredoc(eof);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		perror("faild to fork");
	if (pid == 0)
		heredoc(hd);
	close(hd->fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	*get_status_code() = WEXITSTATUS(status);
	if (*get_status_code() == 130)
	{
		*get_heredoc_check() = false;
		return ;
	}
	redirect_add(redirect,
		redirect_create(HERE_DOC, hd->filename));
}

void	heredoc(t_heredoc *hd)
{
	char	*line;
	int		count;

	signal(SIGINT, sigint_handler);
	count = 1;
	line = readline("> ");
	if (!line)
		heredoc_error(ft_itoa(count), hd->eof);
	while (line && ft_strcmp(line, hd->eof))
	{
		count++;
		if (hd->to_expand)
			line = heredoc_expander(line);
		write(hd->fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
		free(line);
		line = readline("> ");
		if (!line)
			heredoc_error(ft_itoa(count), hd->eof);
	}
	free_all();
	exit(EXIT_SUCCESS);
}
