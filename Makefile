NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

RLFLAG = -lreadline

SRC = intro_to_shell/readline.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)