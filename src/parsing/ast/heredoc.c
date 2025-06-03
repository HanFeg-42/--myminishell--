/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/03 14:12:33 by hfegrach         ###   ########.fr       */
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


void  debug(int sig){
	(void)sig;
	write(2, "here\n", 6);
}

void	heredoc_handler(char *eof, t_file **redirect)
{
	t_heredoc	*hd;
	pid_t		pid;
	int			status;
    // struct termios dflattr;
    // struct termios modattr;

	// tcgetattr(1, &dflattr);
	// modattr = dflattr;
	// modattr.c_cflag &= ~ECHOCTL;
	// tcsetattr(1, TCSANOW,&modattr);
	hd = init_heredoc(eof);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		perror("faild to fork");//dffdxd
	if (pid == 0)
		heredoc(hd);
	close(hd->fd);
	signal(SIGINT, SIG_IGN);//hit ila madrtihach ghadi ybno juj d readlines c_a_d two lines
	waitpid(pid, &status, 0);
	// tcgetattr(1, &dflattr);
	// signal(SIGQUIT, SIG_IGN);

	// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	*get_status_code() = WEXITSTATUS(status);
	if (*get_status_code() == 130)
	{
		*get_heredoc_check() = false;
		return ;
	}
	redirect_add(redirect,
		redirect_create(HERE_DOC, hd->filename));
}

void	sigint_handler(int sig)
{
	(void)sig;
	free_all();
	write(1, "\n", 1);
	exit(130);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	printf("\b");
}

void	heredoc_error(char *nb_line, char *lim)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}

// void	heredoc(t_heredoc *hd)
// {
// 	char	*line;
// 	int		count;
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	count = 1;
// 	write(1, "> ", 2);
// 	line = get_next_line(0);
// 	if (!line)
// 	heredoc_error(ft_itoa(count), hd->eof);
// 	while (line && ft_strcmp(line, hd->lim))
// 	{
// 		count++;
// 		if (hd->to_expand)
// 			line = heredoc_expander(line);
// 		write(hd->fd, line, ft_strlen(line));
// 		free_one(line);
// 		write(1, "> ", 2);
// 		line = get_next_line(0);
// 		if (!line)
// 			heredoc_error(ft_itoa(count), hd->eof);
// 	}
// 	free_one(line);
// 	free_all();
// 	exit(EXIT_SUCCESS);
// }
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
