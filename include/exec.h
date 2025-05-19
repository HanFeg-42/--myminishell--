#ifndef EXEC_H
#define EXEC_H

#include "ast.h"
#include <sys/wait.h>
// #include "minishell.h"


typedef struct s_envp{
	char *key;
	char *value;
	struct s_envp *next;
} t_envp;

typedef enum s_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
} builtin_type;

typedef struct s_pipe
{
	int **pipes;
	int num_of_cmds;
	pid_t *pids;
	int counter;
	
	int saved_stdout;
	int saved_stdin;

} t_pipe;

// -------------------------------------- env functions ------------------------------//
t_envp *env_create(char *key, char *value);
void env_add(t_envp **envp, t_envp *new);
t_envp *get_env_last(t_envp *env);
void get_new_env(t_envp **new_envp, char **old_env);
void print_env(t_envp **env);
t_envp **get_env_head(void);

// ----------------------------------------builtins functions-------------------------//

// ----------------------------------------execution functions -----------------------//

// int execute_shell(t_ast *ast);
void execute_compoud(t_ast *ast);
void execute_pipeline(t_ast *ast);
void execute_command(t_ast *ast, t_pipe *pipeline, int i);
void execute_simple_cmd(t_ast *ast, t_pipe *pipeline, int i);
void execute_subshell(t_ast *ast, t_pipe *pipeline);
int is_builtin(char *cmd);

int *get_status_code();

int *get_error_check(void);

void set_exec_error(const char *msg, int nb);

int ast_size(t_ast *ast);

t_pipe *init_pipes(t_ast *ast);

void close_pipes(t_pipe *pipeline);
void wait_children(t_pipe *pipeline);
void	close_all_pipes(t_pipe *pipeline);


int envp_size(t_envp **old_envp);

char **convert_envp();

char *concat_path(char *path, char *cmd);

char *find_path(char **paths, char *cmd);

char *get_path(char *cmd, char **envp);

void redirect_to_pipe(t_pipe *pipeline, int i);

int type_cmd(char *cmd);

void handle_cmd_error(char *command);

void exec_cmd(t_ast *ast, t_pipe *pipeline, int i, int *fds);

int num_of_redirects(t_file *lst);

void close_redirect(int *fds, int i);

void open_file(t_file *file, int *fds, int i);

int *open_redirects(t_file *redirect);
int execute_builtins(builtin_type type, char **args);
int execute_cd(char *args);

int execute_pwd();

int execute_env();

int execute_export(char *args);
void redirect_io(int fd, t_file *file);
void create_pipes(t_pipe *pipeline);
void ast_advance(t_ast **current);
int *open_redirects(t_file *redirect);
void execute_subshell(t_ast *ast, t_pipe *pipeline);
int is_out_redirect(t_file *file);



#endif