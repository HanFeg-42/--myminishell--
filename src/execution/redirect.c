#include "../../include/exec.h"

int	*open_redirects(t_file *redirect)
{
	t_file	*current;
	int		*fds;
	int		i;
	int		num_of_redirect;

	num_of_redirect = num_of_redirects(redirect);
	fds = ft_malloc(sizeof(int) * num_of_redirect);
	if (!fds)
	{
		set_exec_error("malloc", 1);
		exit(1);
	}
	i = 0;
	current = redirect;
	while (current)
	{
		open_file(current, fds, i);
		if (!(*get_error_check()))
			return (NULL);
		redirect_io(fds[i], current);
		i++;
		current = current->next;
	}
	return (fds);
}

int	num_of_redirects(t_file *lst)
{
	int		len;
	t_file	*current;

	if (!lst)
		return (0);
	current = lst;
	len = 0;
	while (current)
	{
		current = current->next;
		len++;
	}
	return (len);
}

void	close_redirect(int *fds, int i)
{
	while (i >= 0)
	{
		if(fds[i])
			close(fds[i]);
		i--;
	}
}

void	open_file(t_file *file, int *fds, int i)
{
	if (file->type == APPEND)
		fds[i] = open(file->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		fds[i] = open(file->filename, O_RDONLY);
	else
		fds[i] = open(file->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds[i] < 0)
	{
		close_redirect(fds, i - 1);
		set_exec_error(file->filename, 1);
	}
}

void	redirect_io(int fd, t_file *file)
{
	if (file->type == APPEND || file->type == OUTPUT_RED)
		dup2(fd, STDOUT_FILENO);
	else if (file->type == INPUT_RED || file->type == HERE_DOC)
		dup2(fd, STDIN_FILENO);
}