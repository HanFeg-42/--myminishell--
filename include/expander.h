/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:11 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/13 22:23:52 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <dirent.h>
# include "ast.h"
# include "minishell.h"

#define NORMAL 0
#define DOUBLE_QUOTED 1
#define SINGLE_QUOTED 2

#define SQ -1
#define DQ -2
#define STAR -3


typedef struct s_arg
{
	char			*value;
	char			**file;
	struct s_arg	*next;
	struct s_arg	*prev;
}					t_arg;

typedef struct s_expand
{
	t_arg			*arg;
	char			**args;
	char			*word;
	int				i;
	int				stat;
	int				pos;
	char 			**cwd_files;
}					t_expand;

char				**expander(char **args);
t_expand			*init_expand(char **args);
void				expand_parameter(t_expand *exp);
void				copy_characters_until_quote(t_expand *exp, char *file);
void				expand_inside_double_quote(t_expand *exp, char *file);
void				expand_unquoted(t_expand *exp, char *file);
char				*first_quote_occ(char *str);
void				field_split(t_expand *exp);
void				arg_add(t_arg **head, t_arg *new);
t_arg				*arg_create(char *value);
char				**copy_arr(char **arg);
char				*replace_quotes(char *var);
void				expand_pathname(t_expand *exp);
char				**remove_hidden_files(char **files);
void				replace_unquoted_asterisk(t_expand *exp);
char				**get_cwd_files(void);
char				**remove_quotes_from_all(t_expand *exp);
char				*undo_char_changes(char *str);
int					is_match(char *s, char *p);
void	arg_traversal(t_expand *exp, t_arg *arg);
void	track_positions(char **star, char **p_pos, char **s, char **p);
void	append_to_array(char ***var, size_t *size, char *append);
int	is_ifs(int c);
int	is_quoted(char *eof);
int	is_directory(char *pathname);
char	**get_files(t_expand *exp, t_arg *arg);


#endif
