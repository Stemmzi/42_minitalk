NAME = server
NAMEC = client
SRCS = server.c client.c
OBJ = $(SRCS:.c=.o)
LIBFT = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: libft $(NAME) $(NAMEC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) server.o libft.a -o $(NAME)

$(NAMEC): $(OBJ)
	$(CC) $(CFLAGS) client.o libft.a -o $(NAMEC)

libft:
	@make -C libft
	@cp libft/libft.a .

bonus: all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f libft.a
	rm -f $(NAME)
	rm -f $(NAMEC)
	@make -C libft fclean

re: fclean all

.PHONY: all libft clean fclean re
