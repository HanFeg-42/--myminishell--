NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

RLFLAG = -lreadline

SRC = intro_to_shell/readline.c

OBJ = ${SRC:.c=.o}

LIBFT_DIR = ./libft

LIBFT = libft/libft.a

PRINTF_DIR = ./ft_printf

FT_PRINTF = ft_printf/ft_printf.a

CLEAN = clean

FCLEAN = fclean

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -s -C $(LIBFT_DIR)
	$(MAKE) -s -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(RLFLAG) -o $(NAME)
	echo "compiled"

bonus: all

clean:
	$(MAKE) $(CLEAN) -s -C $(LIBFT_DIR)
	$(MAKE) $(CLEAN) -s -C $(PRINTF_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) $(FCLEAN) -s -C $(LIBFT_DIR)
	$(MAKE) $(FCLEAN) -s -C $(PRINTF_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re