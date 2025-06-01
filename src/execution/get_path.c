#include "../../include/exec.h"

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	if (!cmd[0] || cmd[0] == '.')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_path(paths, cmd));
}

char	*concat_path(char *path, char *cmd)
{
	char	*fullpath;
	char	*tmp;

	if (!path || !cmd)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	fullpath = ft_strjoin(tmp, cmd);
	free(tmp);
	return (fullpath);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*fullpath;

	i = 0;
	while (paths[i])
	{
		fullpath = concat_path(paths[i], cmd);
		if (fullpath && access(fullpath, X_OK) == 0)
		{
			return (fullpath);
		}
		i++;
	}
	return (NULL);
}
