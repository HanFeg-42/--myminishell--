#include "../../include/exec.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (-1);
}
void	execute_builtins(int type, char **args)
{
	if (type == ECHO)
		return (execute_echo(args));
	if (type == CD)
		return (execute_cd(args + 1));
	if (type == PWD)
		return (execute_pwd());
	if (type == EXPORT)
		return (execute_export(args + 1));
	if (type == UNSET)
		return (execute_unset(args + 1));
	if (type == ENV)
		return (execute_env());
	if (type == EXIT)
		return (execute_exit(args));
}
