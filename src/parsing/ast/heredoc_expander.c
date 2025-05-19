#include "../../../include/ast.h"

char    *heredoc_expander(char *s)
{
	char    *ret;
	char    *dollar_pos;

	if (!s)
		return (NULL);
	ret = ft_strdup("");
	while(*s)
	{
		dollar_pos = ft_strchr(s, '$');
		if (!dollar_pos)
		{
			ret = ft_strjoin(ret, s); // need new strjoin that returns s1 if !s2
			break;
		}
		ret = ft_strjoin(ret,
			ft_substr(s, 0, dollar_pos - s)); // need new substr that start always = 0
		ret = ft_strjoin(ret, get_env_name(dollar_pos));
		s = skip_env_var(dollar_pos + 1);
	}
	return (ret);
}

char    *get_env_name(char *s)
{
	char    *var;
	int i;

	i = 1;
	/*
	zidi $?
	if (s[i] == '?')
		return (ft_itoa(get_exit_status()));
	========================================
	zidi ila kan s[i] = '$' <-- priority
	*/
	while (s[i] && ft_isalpha(s[1]) && (s[i] == '_' || ft_isalnum(s[i])))
		i++;
	if (i == 1)
		return (ft_strdup("$"));
	var = ft_substr(s, 1, i - 1);
	var = ft_getenv(var);
	var = replace_quotes(var);
	return (var);
}

char *replace_quotes(char *var)
{
	char *ret;
	int i;

	if (!var)
		return (NULL);
	ret = ft_malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (var[i])
	{
		if (var[i] == 39)
			ret[i] = -1; // single quote
		else if (var[i] == 34)
			ret[i] = -2; // double quote
		else
			ret[i] = var[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char    *skip_env_var(char *s)
{
	while (*s && ft_isalpha(s[0]) && (*s == '_' || ft_isalnum(*s)))
		s++;
	return (s);
}

char *ft_getenv(char *var)
{
	// t_envp *current;

	// current = *get_env_head();
	// while (current)
	// {
	//     if (ft_strcmp(current->key, var) == 0)
	//         return (current->value);
	//     current = current->next;
	// }
	// return (NULL);
	return (getenv(var));
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (unsigned char)(*s1) - (unsigned char)(*s2);
}

