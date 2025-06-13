/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_seters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstitou <gstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:47 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/13 21:55:56 by gstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	*get_error_check(void)
{
	static int	check = true;

	return (&check);
}

void	set_exec_error(const char *msg, int nb)
{
	if (msg)
		perror(msg);
	*get_error_check() = false;
	*get_status_code() = nb;
}

void	handle_cmd_error(char *command, t_ast *ast, t_cmd *cmd)
{
	ft_putstr_fd(command, 2);
	if (!ft_strncmp(command, "/", 1))
		ft_putstr_fd(" : No such file or directory", 2);
	else
		ft_putstr_fd(" : command not found", 2);
	ft_putstr_fd("\n", 2);
	cleanup(ast, cmd);
	exit(127);
}

void	print_error1(char *path)
{
	if (!ft_strcmp(path, "."))
	{
		ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories", 2);
		perror (" ");
	}
}

void	print_error2(char *path)
{
	if (!ft_strcmp(path, ".."))
	{
		ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories", 2);
		perror (" ");
	}
}
