NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror# -fsanitize=address -g3

RLFLAG = -lreadline

SRC = src/main.c \
		src/parsing/lexer/token.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/lexer_advancer.c \
		src/parsing/lexer/lexer_getter.c \
		src/parsing/lexer/lexer_skipper.c \
		src/parsing/lexer/cleanup.c \
		src/parsing/lexer/getters.c \
		garbage_collector/free_address.c \
		garbage_collector/free_all.c \
		garbage_collector/ft_malloc.c \
		garbage_collector/getter.c  \
		src/parsing/ast/ast.c \
		src/parsing/ast/ast_helper.c \
		src/parsing/ast/ast_helper2.c \
		src/parsing/ast/parser.c \
		src/parsing/ast/heredoc.c \
		src/parsing/ast/heredoc_expander.c \
		src/parsing/ast/get_next_line.c \
		src/parsing/expander/expand.c \
		src/parsing/expander/expand_param.c \
		src/parsing/expander/field_split.c \
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