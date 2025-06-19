NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3

RLFLAG = -lreadline

SRC = src/main.c \
		garbage_collector/gc_free_address.c \
		garbage_collector/gc_free_all.c \
		garbage_collector/gc_alloc.c \
		garbage_collector/gc_head.c  \
		src/getters/getters.c \
		src/getters/reset_getter.c \
		src/parsing/lexer/token.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/lexer_advancer.c \
		src/parsing/lexer/lexer_getter.c \
		src/parsing/lexer/lexer_checker.c \
		src/parsing/ast/ast.c \
		src/parsing/ast/ast_redirect.c \
		src/parsing/ast/ast_init.c \
		src/parsing/ast/ast_utils.c \
		src/parsing/ast/parser.c \
		src/parsing/ast/heredoc.c \
		src/expansion/expansion_utils.c \
		src/execution/env.c \
		src/execution/exec_compound.c \
		src/execution/exec_command.c \
		src/execution/manage_standards.c \
		src/execution/size.c \
		src/execution/exec_simple_cmd.c \
		src/execution/exec_pipeline.c \
		src/execution/simple_cmd_helpers.c \
		src/execution/builtins.c \
		src/execution/builtins/ft_export.c \
		src/execution/builtins/export_helper.c \
		src/execution/builtins/ft_cd.c \
		src/execution/builtins/ft_echo.c \
		src/execution/builtins/ft_env.c \
		src/execution/builtins/ft_pwd.c \
		src/execution/builtins/ft_exit.c \
		src/execution/builtins/ft_unset.c \
		src/execution/exec_subshell.c \
		src/expansion/expand.c \
		src/expansion/expand_parameter.c \
		src/expansion/field_split.c \
		src/expansion/expand_helper.c \
		src/expansion/field_split_utils.c \
		src/expansion/expand_filename.c \
		src/expansion/quote_removal.c \
		src/expansion/expand_pathname.c \
		src/expansion/checkers.c \
		src/execution/redirect.c \
		src/execution/get_next_line.c \
		src/execution/get_path.c \
		src/execution/error_seters.c \
		src/execution/env_helpers.c \
		src/execution/cleanup.c \
		src/expansion/size_getter.c \
		src/signal.c \
		src/errors.c \
		src/expansion/expand_pathname_utils.c \
		src/execution/get_next_line_utils.c


# src = $(wildcard folder/f2/*.c) $(wildcard folder/*.c)
OBJ = ${SRC:.c=.o}

LIBFT_DIR = ./libft

LIBFT = libft/libft.a

CLEAN = clean

FCLEAN = fclean

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
	@echo "\033[1;32m✅ Compiled successfully\033[0m"

bonus: all

clean:
	@$(MAKE) $(CLEAN) -s -C $(LIBFT_DIR)
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) $(FCLEAN) -s -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
.SECONDARY: