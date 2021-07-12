SRCS = 	srcs/main.c	\
		srcs/init_utils.c \
		srcs/print_utils.c \
		srcs/time_utils.c \
		srcs/monitor.c \
		srcs/routine.c
		
OBJ = $(SRCS:.c=.o)

NAME = philo

INCLUDE = ./include/

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -pthread -I $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread -I $(INCLUDE) $(OBJ) -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: clean fclean all re
