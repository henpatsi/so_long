/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/17 10:09:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42.h"

# ifndef TILE_SIZE
#  define TILE_SIZE 50
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

# ifndef ANIM_DELAY
#  define ANIM_DELAY 0.2
# endif
# ifndef PLAYER_ANIM_0
#  define PLAYER_ANIM_0 "./textures/animated_player/0.png"
# endif
# ifndef PLAYER_ANIM_1
#  define PLAYER_ANIM_1 "./textures/animated_player/1.png"
# endif
# ifndef PLAYER_ANIM_2
#  define PLAYER_ANIM_2 "./textures/animated_player/2.png"
# endif
# ifndef PLAYER_ANIM_3
#  define PLAYER_ANIM_3 "./textures/animated_player/3.png"
# endif

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

typedef struct s_player
{
	int			x;
	int			y;
	mlx_image_t	*img;
	int			inst;
}	t_player;

typedef struct s_gridpos
{
	int			x;
	int			y;
	char		label;
	mlx_image_t	*tile_img;
	mlx_image_t	*obj_img;
	int			tile_inst;
	int			obj_inst;

}	t_gridpos;

typedef struct s_map
{
	t_gridpos		**grid;
	int				size[2];
	int				collectibles;
	int				tile_size;
	t_player		player;
	t_images		images;
	mlx_image_t		*player_anims[4];
	mlx_image_t		*moves_img;
	mlx_t			*mlx;
}	t_map;

t_map			*parse_map(char	*map_file);
int				check_map(char	*map_file, int size[]);
int				check_grid(t_gridpos **grid, int size[], t_player *player);

int				start_game(t_map *map);
void			move_player(t_map *map, int up, int right);

int				initialize_images(mlx_t *mlx, t_map *map);
int				place_images(mlx_t *mlx, t_map *map, t_images *images);

void			resize_tiles(int width, int height, void *param);
int				resize_images(t_images images, int new_size);
int				resize_player_animations(mlx_image_t *images[], int new_size);
void			limit_to_monitor_size(mlx_t *mlx, t_map *map);

mlx_instance_t	*get_tile(t_map *map, int x, int y);
mlx_instance_t	*get_object(t_map *map, int x, int y);
mlx_instance_t	*get_player(t_map *map);

int				free_map(t_map *map);
int				free_grid(t_gridpos **grid);

int				try_open_file(char	*file);
int				game_error(mlx_t *mlx, t_map *map);
int				map_error(char *error_message);

void			animate_player(t_map *map);

#endif