NAME	= philo
SRCS	= main.c utils.c process.c
OBJS	= $(SRCS:.c=.o)
CC		= cc -Wall -Wextra -Werror -I.

# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -Iincludes -c $< -o $@ -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
# $(CC) $(OBJS) -o $(NAME)
	$(CC) $(OBJS) -o $(NAME) -fsanitize=address

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
