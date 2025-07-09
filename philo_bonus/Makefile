CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=philo
SRCS=	main.c \
		src/utils.c \
		src/initializer.c \
		src/handlers.c \
		src/philo.c \

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