CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_printf.a
SRC = 	ft_printf.c			ft_subprint.c	ft_character.c \
		ft_hexadecimal.c	ft_unsigned.c	ft_decint.c	\
		ft_pointer.c		ft_string.c		ft_strlen.c
OBJ =	${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJ)