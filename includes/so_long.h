/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/08 13:54:32 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_WIDTH
#  define TILE_WIDTH 50
# endif
# ifndef TILE_HEIGHT
#  define TILE_HEIGHT 50
# endif

# ifndef FLOOR_TEXTURE
#  define FLOOR_TEXTURE "./textures/floor.png"
# endif
# ifndef WALL_TEXTURE
#  define WALL_TEXTURE "./textures/wall.png"
# endif
# ifndef PLAYER_TEXTURE
#  define PLAYER_TEXTURE "./textures/player.png"
# endif
# ifndef EXIT_TEXTURE
#  define EXIT_TEXTURE "./textures/exit.png"
# endif
# ifndef COLLECTABLE_TEXTURE
#  define COLLECTABLE_TEXTURE "./textures/collectable.png"
# endif

typedef struct s_object
{
	mlx_image_t	*mlx_image;
	int			instance;
}	t_object;

typedef struct s_gridpos
{
	char		label;
	t_object	*object;
}	t_gridpos;

typedef struct s_map
{
	t_gridpos	**grid;
	int			size[2];
	int			collectibles;
	int			player_pos[2];
	t_object	*player;
}	t_map;

int		start_game(t_map *map);
int		initialize_images(mlx_t *mlx, t_map *map);
void	player_key_hook(mlx_key_data_t keydata, void* param);

t_map	*parse_map(char	*map_file);
int		check_extension(char	*map_file);
int		check_symbols(int map_fd, int size[]);
int		check_grid(t_gridpos **grid, int size[], int player[], int *collectibles);

int		ft_strsfree(char **strs);
int		free_map(t_map *map);
int		try_open_file(char	*file);

#endif