NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

RLFLAG = -lreadline

SRC = intro_to_shell/readline.c \
		intro_to_shell/token.c \
		intro_to_shell/lexer.c

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