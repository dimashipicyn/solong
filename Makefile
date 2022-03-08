CC = gcc
FLAGS = -Wall -Wextra -g #-fsanitize=address

SRCS = main.c keys.c render.c loader.c
OBJ = $(SRCS:.c=.o)
NAME = solong.exe
LFT = libft.a
LMLX = libmlx.a

.PHONY: all clean fclean re

all: $(LMLX) $(LFT) $(SRCS) $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) $(LFT) $(LMLX) -framework Appkit -framework OpenGL -o $(NAME)

$(LFT):
		make -C lft
		cp lft/$(LFT) .
		cp lft/libft.h .

$(LMLX):
		make -C lmlx
		cp lmlx/$(LMLX) .

.c.o: $(SRCS)
		$(CC) $(FLAGS) -c $<

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME) $(LFT) $(LMLX)

re: fclean all
