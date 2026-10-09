NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ../minilibx-linux
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext
MATHFLAGS = -lm

SRC = fractol.c fractal_algorithms.c utils.c color_utils.c event_handlers.c ft_atof.c
OBJ = $(SRC:.c=.o)

# Rule for using the libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLXFLAGS) $(MATHFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus

