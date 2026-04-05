NAME = ft_free.a
CC = cc
CFLAGS = -Werror -Wall -Wextra
SRCS =	src/free_str.c \
		src/free_str_array.c \
		src/free_list.c \
		src/free_int_array.c \
		src/ft_free_ultimate.c

INCLUDES = -I includes
OBJS = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
