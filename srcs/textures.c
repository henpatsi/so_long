/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 16:20:28 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void place_tiles(mlx_t *mlx, t_map *map, t_images *images)
{
	int y = 0;
	while (y < map->size[1])
	{
		int x = 0;
		while (x < map->size[0])
		{
			if (map->grid[y][x].label != '1')
			{
				map->grid[y][x].tile_inst = mlx_image_to_window(mlx, images->floor_img, x * map->tile_size, y * map->tile_size);
				map->grid[y][x].tile_img = images->floor_img;
				mlx_set_instance_depth(get_tile(map, x, y), -20);
			}
			else
			{
				map->grid[y][x].tile_inst = mlx_image_to_window(mlx, images->wall_img, x * map->tile_size, y * map->tile_size);
				map->grid[y][x].tile_img = images->wall_img;
				mlx_set_instance_depth(get_tile(map, x, y), -20);
			}
			if (map->grid[y][x].label == 'P')
			{
				map->player.inst = mlx_image_to_window(mlx, images->player_img, x * map->tile_size, y * map->tile_size);
				map->player.img = images->player_img;
				mlx_set_instance_depth(&map->player.img->instances[map->player.inst], 0);
			}
			if (map->grid[y][x].label == 'E')
			{
				map->grid[y][x].obj_inst = mlx_image_to_window(mlx, images->exit_img, x * map->tile_size, y * map->tile_size);
				map->grid[y][x].obj_img = images->exit_img;
				mlx_set_instance_depth(get_object(map, x, y), -10);
			}
			if (map->grid[y][x].label == 'C')
			{
				map->grid[y][x].obj_inst = mlx_image_to_window(mlx, images->collectable_img, x * map->tile_size, y * map->tile_size);
				map->grid[y][x].obj_img = images->collectable_img;
				mlx_set_instance_depth(get_object(map, x, y), -10);
			}
			x++;
		}
		y++;
	}
}

int	initialize_textures(t_textures *textures)
{
	textures->player_tex = mlx_load_png(PLAYER_TEXTURE);
	if (!textures->player_tex)
		return (0);
	textures->floor_tex = mlx_load_png(FLOOR_TEXTURE);
	if (!textures->floor_tex)
		return (0);
	textures->wall_tex = mlx_load_png(WALL_TEXTURE);
	if (!textures->wall_tex)
		return (0);
	textures->exit_tex = mlx_load_png(EXIT_TEXTURE);
	if (!textures->exit_tex)
		return (0);
	textures->collectable_tex = mlx_load_png(COLLECTABLE_TEXTURE);
	if (!textures->collectable_tex)
		return (0);
	return (1);
}

int	initialize_images(t_images *images, t_textures *textures, mlx_t *mlx)
{
	images->player_img = mlx_texture_to_image(mlx, textures->player_tex);
	if (!images->player_img)
		return (0);
	images->floor_img = mlx_texture_to_image(mlx, textures->floor_tex);
	if (!images->floor_img)
		return (0);
	images->wall_img = mlx_texture_to_image(mlx, textures->wall_tex);
	if (!images->wall_img)
		return (0);
	images->exit_img = mlx_texture_to_image(mlx, textures->exit_tex);
	if (!images->exit_img)
		return (0);
	images->collectable_img = mlx_texture_to_image(mlx, textures->collectable_tex);
	if (!images->collectable_img)
		return (0);
	return (1);
}

int	initialize_graphics(mlx_t *mlx, t_map *map, t_images *images)
{
	t_textures	textures;

	if (!initialize_textures(&textures))
		return (0);
	if (!initialize_images(images, &textures, mlx))
		return (0);
	place_tiles(mlx, map, images);
	return (1);
}