NAME = server
NAMEC = client
SRCS = server.c client.c
OBJ = $(SRCS:.c=.o)
LIBFT = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft 
	$(CC) $(CFLAGS) server.c libft.a -o server
	$(CC) $(CFLAGS) client.c libft.a -o client

# $(NAME): libft $(OBJ) $(NAMEC)
# 	$(CC) $(CFLAGS) server.o libft.a -o server

# $(NAMEC):
# 	$(CC) $(CFLAGS) client.o libft.a -o client

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
	rm -f $(NAME)
	rm -f libft.a
	rm -f server
	rm -f client
	@make -C libft fclean

re: fclean all

.PHONY: all libft clean fclean re
