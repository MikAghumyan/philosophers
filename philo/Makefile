CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread
NAME=philo
SRCS=handlers.c \
		main.c \
		initializer.c \
		utils.c \
		philo.c \
		philo_routine.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

debug: CFLAGS += -g
debug: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug