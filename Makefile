NAME = minishell

CC = cc

RM = rm -f

CFLAGS = #-Wall -Wextra -Werror# -fsanitize=address -g3

RLFLAG = -lreadline

SRC = src/main.c \
		src/parsing/lexer/token.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/lexer_advancer.c \
		src/parsing/lexer/lexer_getter.c \
		src/parsing/lexer/lexer_skipper.c \
		src/parsing/lexer/getters.c \
		garbage_collector/free_address.c \
		garbage_collector/free_all.c \
		garbage_collector/ft_malloc.c \
		garbage_collector/getter.c  \
		src/parsing/ast/ast.c \
		src/parsing/ast/ast_redirect.c \
		src/parsing/ast/ast_helper.c \
		src/parsing/ast/ast_helper2.c \
		src/parsing/ast/parser.c \
		src/parsing/ast/ast_print.c \
		src/parsing/ast/heredoc.c \
		src/parsing/ast/heredoc_expander.c \
		src/parsing/ast/realloc_array.c \
		src/parsing/ast/get_next_line.c \
		src/execution/env.c \
		src/execution/exec_compound.c \
		src/execution/exec_command.c \
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
		src/execution/builtins/ft_unset.c \
		src/execution/exec_subshell.c \
		src/parsing/expander/expand.c \
		src/parsing/expander/expand_param.c \
		src/parsing/expander/field_split.c \
		src/parsing/expander/expand_helper.c \
		src/parsing/expander/expamd_helper2.c \
		src/parsing/expander/expand_pathname.c \
		src/parsing/expander/expand_filename.c \
		src/parsing/expander/quote_removal.c \
		src/parsing/expander/expand_helper.c

OBJ = ${SRC:.c=.o}

LIBFT_DIR = ./libft

LIBFT = libft/libft.a

CLEAN = clean

FCLEAN = fclean

HEADER	=	include/minishell.h

all: $(NAME) $(HEADER)

$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
	echo "compiled"

bonus: all

clean:
	@$(MAKE) $(CLEAN) -s -C $(LIBFT_DIR)
	@$(RM) $(OBJ)

fclean: clean
	@$(MAKE) $(FCLEAN) -s -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re