# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 13:12:13 by hpatsi            #+#    #+#              #
#    Updated: 2024/01/16 10:33:27 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

BONUS = .bonus

LIBFT = ./libft/libft.a

MLX42_DIR = ./MLX42/build/

MLX42 = $(MLX42_DIR)libmlx42.a

SOURCE_FILES = so_long game player_control \
			   init_images place_images resize instances \
			   map check_map check_grid free error

SOURCES = $(addsuffix .c, $(addprefix ./srcs/, $(SOURCE_FILES)))

OBJECTS = $(SOURCES:.c=.o)

BONUS_SOURCES = $(addsuffix _bonus.c, $(addprefix ./bonus/, $(SOURCE_FILES)))

BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

HEADERS = -I ./includes -I ./MLX42/include/MLX42

DEPENDENCIES = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

CFLAGS += -Wall -Wextra -Werror $(HEADERS)

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)

$(OBJECTS): $(SOURCES)

bonus: $(BONUS)

$(BONUS): $(BONUS_OBJECTS) $(LIBFT) $(MLX42)
	cc $(CFLAGS) $(BONUS_OBJECTS) $(LIBFT) $(MLX42) $(DEPENDENCIES) -o $(NAME)
	touch $(BONUS)

$(BONUS_OBJECTS): $(BONUS_SOURCES)

$(LIBFT):
	make -C ./libft/

$(MLX42): $(MLX42_DIR)
	make -C $(MLX42_DIR)

$(MLX42_DIR):
	cmake ./MLX42/ -B $(MLX42_DIR)

clean:
	make clean -C ./libft/
	rm -f $(OBJECTS)
	rm -f $(BONUS_OBJECTS)
	make depend -C $(MLX42_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)
	rm -f $(BONUS)
	make clean -C $(MLX42_DIR)

re: fclean all