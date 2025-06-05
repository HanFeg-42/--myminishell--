/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:11 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/04 16:14:02 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <dirent.h>
# include "ast.h"
# include "minishell.h"

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
	char 			**dir_files;
}					t_expand;

char				**expander(char **args);
t_expand			*init_expand(char **args);
void				expand_param(t_expand *exp);
char	**get_dirs(void);
// void				copy_characters_until_quote(t_expand *exp);
// void				expand_inside_double_quote(t_expand *exp);
// void				expand_unquoted(t_expand *exp);
void				copy_characters_until_quote(t_expand *exp, char *file);
void				expand_inside_double_quote(t_expand *exp, char *file);
void				expand_unquoted(t_expand *exp, char *file);
char				*first_quote_occ(char *str);
void				field_split(t_expand *exp);
t_arg				*get_next_field(t_expand *exp);
char				*get_field(t_expand *exp);
char				*first_ifs_occ(char *s);
void				arg_add(t_arg **head, t_arg *new);
t_arg				*arg_create(char *value);
void				print_t_arg(t_arg *arg);
void				exp_skip_whitespaces(t_expand *exp);
char				**copy_arr(char **arg);
char				*replace_quotes(char *var);
void				expand_pathname(t_expand *exp);
void				match_star(t_expand *exp, char **files, t_arg *arg);
char				**remove_hidden_files(char **files);
t_arg				*arg_addmid(t_arg **head, t_arg *mid, t_arg *new);
void				replace_unquoted_asterisk(t_expand *exp);
char				**get_files(void);
char				**remove_quotes_from_all(t_expand *exp);
char				*undo_char_changes(char *str);
int					arg_size(t_arg *arg);
char				*get_pattern(char *str);
char				*wdmatch(char *wd, char *file);
int					is_match(char *s, char *p);
// void expand(t_ast *ast);
// void expand_file(t_file *red);
void paramter_expansion(char *file, t_expand *exp);
int field_splitting(t_expand *exp);
int pathname_expansion(t_expand *exp);
void ambiguous_redirect(char *err);
void	arg_traversal(t_expand *exp, t_arg *arg);
void	track_positions(char **star, char **p_pos, char **s, char **p);
int	hidden_file_size(char **files);
int	append_to_array(char ***var, size_t *size, char *append);
char	**get_root_dirs(void);

#endif
