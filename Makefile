NAME = server
NAMEC = client
NAME_BONUS = server_bonus
NAMEC_BONUS = client_bonus
SRCS = server.c client.c server_bonus.c client_bonus.c
OBJ = $(SRCS:.c=.o)
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME) $(NAMEC)

$(NAME): $(LIBFT) server.o
	$(CC) $(CFLAGS) server.o $(LIBFT) -o $(NAME)

$(NAMEC): client.o
	$(CC) $(CFLAGS) client.o $(LIBFT) -o $(NAMEC)

bonus: $(LIBFT) $(NAME_BONUS) $(NAMEC_BONUS)

$(NAME_BONUS): server_bonus.o
	$(CC) $(CFLAGS) server_bonus.o $(LIBFT) -o $(NAME_BONUS)

$(NAMEC_BONUS): client_bonus.o
	$(CC) $(CFLAGS) client_bonus.o $(LIBFT) -o $(NAMEC_BONUS)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	norminette $(SRCS)

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f libft.a
	rm -f $(NAME) $(NAMEC)
	rm -f $(NAME_BONUS) $(NAMEC_BONUS)
	@make -C libft fclean

re: fclean all

.PHONY: all bonus norm clean fclean re
