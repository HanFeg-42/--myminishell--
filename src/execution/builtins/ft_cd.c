/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:00:06 by gstitou           #+#    #+#             */
/*   Updated: 2025/06/11 20:32:49 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

void	set_error(char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	set_exec_error(NULL, 1);
}

void	change_dir(char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = ft_str_dup(*saved_pwd());
		print_error1(path);
	}
	if (chdir(path) != 0)
		return (free(old_pwd), ft_putstr_fd("cd: ", 2), ft_putstr_fd(path, 2),
			set_exec_error(" ", 1));
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		free(*saved_pwd());
		*saved_pwd() = ft_str_dup(new_pwd);
	}
	else
	{
		new_pwd = ft_str_dup(*saved_pwd());
		print_error2(path);
	}
	update_env(old_pwd, new_pwd);
}

void	execute_cd(char **args)
{
	char	*path;

	if (!args[0] || !ft_strcmp(args[0], "~"))
	{
		path = ft_getenv("HOME");
		if (!path)
			return (set_error("cd: HOME not set\n"));
	}
	else if (args[1])
		return (set_error("cd: too many arguments\n"));
	else
		path = args[0];
	change_dir(path);
}

void	update_env(char *old_pwd, char *new_pwd)
{
	char	**elems;

	elems = gc_alloc(sizeof(char *) * 3);
	if (!elems)
	{
		set_exec_error("malloc:", 1);
		if (new_pwd)
			free(new_pwd);
		if (old_pwd)
			free(old_pwd);
		return ;
	}
	elems[0] = ft_strjoin("PWD=", new_pwd);
	elems[1] = ft_strjoin("OLDPWD=", old_pwd);
	elems[2] = NULL;
	execute_export(elems);
}
