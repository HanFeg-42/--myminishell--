#include "libft.h"

char	*ft_str_dup(const char *str)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = ft_strlen(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}