/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:38:21 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/14 17:48:47 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ast.h"
#include "../../../include/exec.h"
#include "../../../include/heredoc.h"

static char	*generate_name(void)
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

static t_heredoc	*heredoc_init(char *eof)
{
	t_heredoc	*hd;

	hd = gc_alloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->eof = remove_quotes(eof);
	hd->filename = generate_name();
	hd->to_expand = !(is_quoted(eof));
	hd->fd = open(hd->filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!hd->fd)
		perror("failed to open");
	return (hd);
}

static char	*heredoc_expander(char *s)
{
	char	*ret;
	char	*dollar_pos;

	if (!s)
		return (NULL);
	ret = ft_strdup("");
	while (*s)
	{
		dollar_pos = ft_strchr(s, '$');
		if (!dollar_pos)
		{
			ret = ft_strjoin(ret, s);
			break ;
		}
		ret = ft_strjoin(ret,
				ft_substr(s, 0, dollar_pos - s));
		ret = ft_strjoin(ret, get_env_name(dollar_pos));
		s = skip_env_var(dollar_pos + 1);
	}
	return (ret);
}

void	heredoc(t_heredoc *hd)
{
	char	*line;
	char	*saved_line;
	int		count;

	signal(SIGINT, sigint_handler_in_heredoc);
	count = 1;
	saved_line = NULL;
	line = readline("> ");
	if (!line)
		heredoc_error(ft_itoa(count), hd->eof);
	while (line && ft_strcmp(line, hd->eof))
	{
		saved_line = line;
		count++;
		if (hd->to_expand)
			line = heredoc_expander(line);
		write(hd->fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
		free(saved_line);
		line = readline("> ");
		if (!line)
			heredoc_error(ft_itoa(count), hd->eof);
	}
	close(hd->fd);
	clean_and_exit(NULL, EXIT_SUCCESS);
}

void	heredoc_handler(char *eof, t_file **redirect)
{
	t_heredoc	*hd;
	pid_t		pid;
	int			status;

	hd = heredoc_init(eof);
	ignore_signals();
	pid = fork();
	if (pid < 0)
		perror("faild to fork");
	if (pid == 0)
		heredoc(hd);
	close(hd->fd);
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
