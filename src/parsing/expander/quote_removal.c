#include "../../../include/expander.h"

int append_to_array(char **arr, size_t *size, char *append)
{
	arr = ft_realloc(arr, sizeof(char *) * (*size + 2));
	if (!arr)
		return (false);
	arr[(*size)++] = append;
	arr[*size] = NULL;
	return (true);
}

char **remove_quotes_from_all(t_expand *exp)
{
	char **result;
	size_t i;
	size_t j;

	i = 0;
	result = NULL;
	while (exp->arg)
	{
		if (exp->arg->file)
		{
			j = 0;
			while (exp->arg->file[j])
			{
				if (!append_to_array(result, &i, ft_strdup(exp->arg->file[j]))) // yqder ywq3 mochkil bsbab j
					return (NULL);
				j++;
			}
			// {
			// 	result = ft_realloc(result, sizeof(char *) * (i + 2));
			// 	if (!result)
			// 		return (NULL);
			// 	result[i++] = ft_strdup(exp->arg->file[j++]);
			// 	result[i] = NULL;
			// }
		}
		else if (!append_to_array(result, &i, undo_char_changes(remove_quotes(exp->arg->value))))
			return (NULL);
		// {
		// 	ret = ft_realloc(ret, sizeof(char *) * (i + 2));
		// 	if (!ret)
		// 		return (NULL);
		// 	ret[i++] = undo_char_changes(remove_quotes(exp->arg->value));
		// 	ret[i] = NULL;
		// }
		exp->arg = exp->arg->next;
	}
	return (result);
}

