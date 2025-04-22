NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

RLFLAG = -lreadline

SRC = intro_to_shell/main.c \
		intro_to_shell/token.c \
		intro_to_shell/lexer.c \
		intro_to_shell/lexer_advancer.c \
		intro_to_shell/lexer_getter.c \
		intro_to_shell/lexer_skipper.c \
		intro_to_shell/get_next_line.c \
		intro_to_shell/cleanup.c \
		garbage_collector/free_address.c \
		garbage_collector/free_all.c \
		garbage_collector/ft_malloc.c \
		garbage_collector/getter.c \
		intro_to_shell/parser.c \
		intro_to_shell/getters.c

OBJ = ${SRC:.c=.o}

LIBFT_DIR = ./libft

LIBFT = libft/libft.a

CLEAN = clean

FCLEAN = fclean

HEADER	=	include/minishell.h

all: $(NAME) $(HEADER)

$(NAME): $(OBJ)
	$(MAKE) -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
	echo "compiled"

bonus: all

clean:
	$(MAKE) $(CLEAN) -s -C $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) $(FCLEAN) -s -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re