#include "include/minishell.h"
#include "include/exec.h"

int *get_status_code()
{
	static int status = 0;
	return (&status);
}

// this is hsdfa
int is_numeric(char *nbr)
{
	int i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (false);
		i++;
	}
	return (true);
}

void    m_exit(char **av)
{
	ft_putendl_fd(av[0], 1);
	if (!av[1])
		exit(*get_status_code());
	if (!is_numeric(av[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (av[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		*get_status_code() = 1;
	}
	else
		exit((unsigned char)ft_atoi(av[1]));
}
// exit: too many arguments
// exit: jfdsklj: numeric argument required
int main(int ac, char **av)
{
	(void)ac;
	m_exit(av);
	return (*get_status_code());
}