#include "../../../include/ast.h"
#include "../../../include/heredoc.h"

char *generate_name(void)
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

void    heredoc_handler(char *eof, t_file **redirect)
{
	t_heredoc *hd;
	pid_t pid;
	int status;

	if (!(*get_heredoc_check()))
		return ;
	hd = init_heredoc(eof);
	pid = fork();
	if (pid < 0)
		perror("faild to fork");// handli l error w bdli l error chechker o dakchi
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

t_heredoc	*init_heredoc(char *eof)
{
	t_heredoc	*hd;

	hd = ft_malloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->filename = generate_name();
	hd->to_expand = !(is_quoted(eof));
	hd->lim = ft_strjoin(remove_quotes(eof), "\n");
	hd->fd = open(hd->filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
	if (!hd->fd)
		perror("failed to open");
	// handle if open faild
	return (hd);
}

void	SIGINT_handler(int sig)
{
	(void)sig;
	free_all();
	exit(130);
}

void	heredoc2(t_heredoc *hd)
{
	// use a struct to keep all these
	char	*line;

	signal(SIGINT, SIGINT_handler);
	// signal(SIGINT, SIG_DFL);
	line = get_next_line(0);
	while (line && ft_strcmp(line, hd->lim)) // limmmmm == lim
	{
		if (hd->to_expand)
			line = heredoc_expander(line);
		write(hd->fd, line, ft_strlen(line));
		free_one(line);
		line = get_next_line(0);
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

int is_quoted(char *eof)
{
	if (ft_strchr(eof, 34) || ft_strchr(eof, 39))
		return (true);
	return (false);
}

char *remove_quotes(char *str)
{
	int stat;
	int i;
	int j;
	char *ret;

	ret = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (NULL);
	(stat = 0, i = 0, j = 0);
	while (str[i])
	{
		if (str[i] == 34 && stat == 0) // inside double quotes
			stat = 1;
		else if ((str[i] == 34 && stat == 1) || (str[i] == 39 && stat == 2)) // khrjt mn l quoted stat + now on normal stat
			stat = 0;
		else if (str[i] == 39 && stat == 0) // inside single quotes
			stat = 2;
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

//TODO:======================= is_quoted --> DONE
//TODO:======================= quote_removal
//TODO:======================= heredoc_expander