NAME	= philo
SRCS	= main.c utils.c utils2.c time.c init.c error.c philo.c game.c
OBJS	= $(SRCS:.c=.o)
CC		= cc -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
# $(CC) $(OBJS) -o $(NAME)
	$(CC) $(OBJS) -o $(NAME) -fsanitize=address -pthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
