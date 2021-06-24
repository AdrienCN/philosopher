SRCS = srcs/main.c

OBJ = $(SRCS:.c=.o)

NAME = philo

INCLUDE = ./include/

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJ) -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: clean fclean all re
