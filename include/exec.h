/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfegrach <hfegrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:43:31 by hfegrach          #+#    #+#             */
/*   Updated: 2025/06/18 17:36:13 by hfegrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
# include "lexer.h"
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef enum s_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}					t_builtin_type;

typedef struct s_pipe
{
	int				*pipefd;
	pid_t			*pids;
	int				num_of_cmds;
	int				counter;
	int				saved_stdin;
}					t_pipe;

typedef struct s_cmd
{
	int				type;
	int				pos;
	t_pipe			*pipeline;
	char			**envp;
	char			*pathname;
	int				saved_stdout;
	int				saved_stdin;
}					t_cmd;

t_envp				*env_create(char *key, char *value);
void				env_add(t_envp **envp, t_envp *new);
t_envp				*get_env_last(t_envp *env);
void				get_new_env(t_envp **new_envp, char **old_env);
t_envp				**get_env_head(void);
void				execute_compound(t_ast *ast);
void				execute_pipeline(t_ast *ast);
void				execute_command(t_ast *ast, t_pipe *pipeline, int i);
void				execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i);
void				execute_subshell(t_ast *ast, t_pipe *pipeline);
int					is_builtin(char *cmd);
int					*get_status_code(void);
int					*get_error_check(void);
void				set_exec_error(const char *msg, int nb);
int					ast_size(t_ast *ast);
void				wait_children(t_pipe *pipeline);
void				free_all_env(t_envp **envp);
int					envp_size(t_envp **old_envp);
char				**convert_envp(void);
char				*concat_path(char *path, char *cmd);
char				*find_path(char **paths, char *cmd);
char				*get_path(char *cmd, char **envp);
int					type_cmd(char *cmd);
void				handle_cmd_error(char *command);
void				exec_cmd(t_ast *ast, t_cmd *cmd);
int					open_file(t_file *file);
int					num_of_redirects(t_file *lst);
void				open_redirects(t_file *redirect);
void				execute_builtins(int type, char **args);
void				redirect_io(int fd, t_file *file);
void				ast_advance(t_ast **current);
void				execute_subshell(t_ast *ast, t_pipe *pipeline);
void				restore_standards(t_cmd *cmd);
void				dup_standards(t_cmd *cmd);
void				restore_stdin(t_pipe *pipeline);
void				setup_process_pipes(t_pipe *pipeline, int i);
char				*ft_getenv(char *var);
void				set_error(char *str);
void				update_env(char *old_pwd, char *new_pwd);
void				execute_cd(char **args);
void				execute_pwd(void);
void				execute_env(char **args);
void				handle_single_export(char *arg, t_envp **envp);
void				execute_export(char **args);
t_envp				*find_node(char *key);
void				free_env(void *key);
void				execute_unset(char **args);
void				execute_exit(char **av);
int					skip_option(char **arg, int *i);
void				execute_echo(char **arg);
int					execute_single_built(t_cmd *cmd, t_ast *ast);
int					is_key_valid(char *arg);
void				swap_nodes(t_envp *curr, t_envp *node);
void				sort_envp(t_envp **head);
void				print_sorted_env(t_envp **envp);
t_envp				**copy_env(t_envp **envp);
void				handle_process(t_ast *ast, t_cmd *cmd);
void				setup_redirects(t_ast *ast);
void				and_or_handler(t_ast **current);
char				**saved_pwd(void);
void				set_error(char *str);
void				clean_and_exit(int nb);
void				change_dir(char *path);
void				print_error1(char *args);
void				print_error2(char *args);
void				update_export(t_envp **envp, char *key, char *value);
t_pipe				*init_pipeline(t_ast *ast);
int					*get_num_cmds(void);
void				close_pipe(int *pipefd);
void				handle_empty_args(t_ast *ast, t_cmd *cmd);
void				setup_only_redirect(t_file *redirect, t_cmd *cmd);
void				is__directory(char *cmd);
#endif