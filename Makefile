# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 13:12:13 by hpatsi            #+#    #+#              #
#    Updated: 2024/01/12 14:13:40 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libft/libft.a

MLX42_DIR = ./MLX42/build/

MLX42 = $(MLX42_DIR)libmlx42.a

SOURCES = $(addprefix ./srcs/, so_long.c game.c player_control.c \
							   init_images.c resize.c instances.c\
							   map.c check_map.c check_grid.c free.c error.c)

OBJECTS = $(SOURCES:.c=.o)

HEADERS = -I ./includes -I ./MLX42/include/MLX42

DEPENDENCIES = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

CFLAGS += -Wall -Wextra -Werror $(HEADERS)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

$(OBJECTS): $(SOURCES)

$(LIBFT):
	make -C ./libft/

$(MLX42): $(MLX42_DIR)
	make -C $(MLX42_DIR)

$(MLX42_DIR):
	cmake ./MLX42/ -B $(MLX42_DIR)

clean:
	make clean -C ./libft/
	rm -f $(OBJECTS)
	make depend -C $(MLX42_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	make clean -C $(MLX42_DIR)

re: fclean all