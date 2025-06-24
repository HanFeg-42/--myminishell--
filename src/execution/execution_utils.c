/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 23:09:40 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/20 00:19:31 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include "../../include/heredoc.h"

int	ast_size(t_ast *ast)
{
	int		i;
	t_ast	*current;

	current = ast->first_child;
	i = 0;
	while (current)
	{
		current = current->next_sibling;
		i++;
	}
	return (i);
}

int	expand_heredoc_file(int fd, t_file *file)
{
	char	*line;
	char	*eof;
	int		heredoc_fd;
	int		to_expand;

	file->expanded = generate_name();
	to_expand = !(is_quoted(file->delimiter));
	eof = ft_strjoin(remove_quotes(file->delimiter), "\n");
	heredoc_fd = open(file->expanded, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		set_exec_error(file->expanded, 1);
	line = get_next_line(fd);
	while (line && ft_strcmp(line, eof))
	{
		if (to_expand)
			line = heredoc_expander(line);
		write(heredoc_fd, line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (restore_heredoc_offset(heredoc_fd, file->expanded));
}

void	unlink_heredoc_files(t_ast *ast)
{
	t_ast	*current;
	t_ast	*child;

	current = ast->first_child;
	while (current)
	{
		child = current->first_child;
		if (child->type == AST_SIMPLE_CMD)
		{
			while (child->redirect)
			{
				if (child->redirect->type == HERE_DOC)
					unlink(child->redirect->filename);
				child->redirect = child->redirect->next;
			}
		}
		ast_advance(&current);
	}
	if (access(HDOC_EXPANDED_PATH, F_OK) == 0)
		unlink(HDOC_EXPANDED_PATH);
}
