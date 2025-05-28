/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/05/28 15:08:32 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
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

	hd = ft_malloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->eof = remove_quotes(eof);
	hd->filename = generate_name();
	hd->to_expand = !(is_quoted(eof));
	hd->lim = ft_strjoin(hd->eof, "\n");
	hd->fd = open(hd->filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!hd->fd)
		perror("failed to open");//drxyhsr
	return (hd);
}

void	heredoc_handler(char *eof, t_file **redirect)
{
	t_heredoc	*hd;
	pid_t		pid;
	int			status;

	if (!(*get_heredoc_check()))
		return ;
	hd = init_heredoc(eof);
	pid = fork();
	if (pid < 0)
		perror("faild to fork");//dffdxd
	if (pid == 0)
		heredoc2(hd);
	close(hd->fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		*get_heredoc_check() = false;
		return ;
	}
	redirect_add(redirect,
		redirect_create(HERE_DOC, hd->filename));
}

// handle if open faild !!!!!!!!!!!!!!!!!!!!!!!!!!!!

void	sigint_handler(int sig)
{
	(void)sig;
	free_all();
	exit(130);
}

void	heredoc_error(char *nb_line, char *lim)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}
//warning: here-document at line 1 delimited by end-of-file (wanted `h')
void	heredoc2(t_heredoc *hd)
{
	char	*line;
	int		count;

	signal(SIGINT, sigint_handler);
	count = 0;
	line = get_next_line(0);
	if (!line)
		heredoc_error(ft_itoa(count), hd->eof);
	while (line && ft_strcmp(line, hd->lim))
	{
		count++;
		if (hd->to_expand)
			line = heredoc_expander(line);
		write(hd->fd, line, ft_strlen(line));
		free_one(line);
		write(2,"hi",2);
		line = get_next_line(0);
		if (!line)
			heredoc_error(ft_itoa(count), hd->eof);
	}
	free_one(line);
	free_all();
	exit(EXIT_SUCCESS);
}

// void	heredoc(char *eof, t_file **redirect)
// {
// 	// use a struct to keep all these
// 	char *lim;
// 	int to_expand;
// 	int fd;
// 	char *line;
// 	char	*filename;

// 	filename = generate_name();
// 	to_expand = !(is_quoted(eof));
// 	lim = remove_quotes(eof);
// 	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
// 	line = get_next_line(0);
// 	while (line && ft_strcmp(line, lim)) // limmmmm == lim
// 	{
// 		if (to_expand)
// 			line = heredoc_expander(line);
// 		write(fd, line, ft_strlen(line));
// 		free_one(line);
// 		line = get_next_line(0);
// 	}
// 	free_one(line);
// 	close(fd);
// 	redirect_add(redirect,
// 		redirect_create(HERE_DOC, filename));
// 	return ;
// }

//TODO:======================= is_quoted --> DONE
//TODO:======================= quote_removal
//TODO:======================= heredoc_expander