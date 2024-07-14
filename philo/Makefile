NAME	= philo
SRCS	= main.c utils.c time.c init.c error.c philo.c init2.c mutex.c
OBJS	= $(SRCS:.c=.o)
CC		= cc -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
# $(CC) $(OBJS) -o $(NAME) -pthread --fsanitize=thread
	$(CC) $(OBJS) -o $(NAME) -pthread -fsanitize=thread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
