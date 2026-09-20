# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: souichou <marvin@42.fr>                    +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2026/01/22 00:00:00 by souichou          #+#    #+#             #
#    Updated: 2026/01/22 00:00:00 by souichou         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_PATH	= ../minilibx-linux
MLX_LIB		= $(MLX_PATH)/libmlx.a
MLX_FLAGS	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

INC_DIR		= includes
SRC_DIR		= src
OBJ_DIR		= obj

INCLUDES	= -I$(INC_DIR) -I$(MLX_PATH)


SRCS		= $(SRC_DIR)/cleanup.c \
			  $(SRC_DIR)/cleanup2.c \
			  $(SRC_DIR)/event_hooks.c \
			  $(SRC_DIR)/game_management.c \
			  $(SRC_DIR)/game_management_utils.c \
			  $(SRC_DIR)/gnl.c \
			  $(SRC_DIR)/gnl_utils.c \
			  $(SRC_DIR)/init_game.c \
			  $(SRC_DIR)/init_game_utils.c \
			  $(SRC_DIR)/main.c \
			  $(SRC_DIR)/movement.c \
			  $(SRC_DIR)/parse_colors.c \
			  $(SRC_DIR)/parse_colors_utils.c \
			  $(SRC_DIR)/parse_elements.c \
			  $(SRC_DIR)/parse_map.c \
			  $(SRC_DIR)/parse_map_utils.c \
			  $(SRC_DIR)/parse_textures.c \
			  $(SRC_DIR)/parse_utils.c \
			  $(SRC_DIR)/parse_utils2.c \
			  $(SRC_DIR)/raycast.c \
			  $(SRC_DIR)/raycast_utils.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/textures.c \
			  $(SRC_DIR)/textures_utils.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/utils2.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
