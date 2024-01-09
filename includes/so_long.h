/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 14:15:43 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 160
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

typedef struct s_player
{
	int	x;
	int	y;
	mlx_instance_t	*instance;
}	t_player;

typedef struct s_gridpos
{
	char			label;
	mlx_instance_t	*tile;
	mlx_instance_t	*object;
}	t_gridpos;

typedef struct s_map
{
	t_gridpos	**grid;
	int			size[2];
	int			collectibles;
	int			tile_size;
	t_player	player;
}	t_map;

typedef struct s_textures
{
	mlx_texture_t	*player_tex;
	mlx_texture_t	*floor_tex;
	mlx_texture_t	*wall_tex;
	mlx_texture_t	*exit_tex;
	mlx_texture_t	*collectable_tex;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*player_img;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*exit_img;
	mlx_image_t	*collectable_img;
}	t_images;

int		start_game(t_map *map);
int		initialize_graphics(mlx_t *mlx, t_map *map, t_images *images);
void	player_key_hook(mlx_key_data_t keydata, void* param);

t_map	*parse_map(char	*map_file);
int		check_extension(char	*map_file);
int		check_symbols(int map_fd, int size[]);
int		check_grid(t_gridpos **grid, int size[], int player[], int *collectibles);

int		ft_strsfree(char **strs);
int		free_map(t_map *map);
int		try_open_file(char	*file);

#endif