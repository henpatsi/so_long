/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 13:03:22 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_tile_order(t_map *map, t_images *images, int floor_count)
{
	int i = 0;
	while (i < floor_count)
	{
		mlx_set_instance_depth(&images->floor_img->instances[i], -20);
		i++;
	}
	i = 0;
	while (i < map->collectibles)
	{
		mlx_set_instance_depth(&images->collectable_img->instances[i], 0);
		i++;
	}
	mlx_set_instance_depth(&map->player->mlx_image->instances[0], 10);
}

void place_tiles(mlx_t *mlx, t_map *map, t_images *images)
{
	int	floor_count;
	int	collectable_count;

	int y = 0;
	floor_count = 0;
	collectable_count = 0;
	while (y < map->size[1])
	{
		int x = 0;
		while (x < map->size[0])
		{
			if (map->grid[y][x].label != '1')
			{
				mlx_image_to_window(mlx, images->floor_img, x * TILE_WIDTH, y * TILE_HEIGHT);
				floor_count++;
			}
			else
				mlx_image_to_window(mlx, images->wall_img, x * TILE_WIDTH, y * TILE_HEIGHT);
			if (map->grid[y][x].label == 'P')
			{
				mlx_image_to_window(mlx, images->player_img, x * TILE_WIDTH, y * TILE_HEIGHT);
				map->player->mlx_image = images->player_img;
			}
			if (map->grid[y][x].label == 'E')
				mlx_image_to_window(mlx, images->exit_img, x * TILE_WIDTH, y * TILE_HEIGHT);
			if (map->grid[y][x].label == 'C')
			{
				mlx_image_to_window(mlx, images->collectable_img, x * TILE_WIDTH, y * TILE_HEIGHT);
				map->grid[y][x].object = malloc(sizeof (t_object));
				map->grid[y][x].object->instance = collectable_count;
				map->grid[y][x].object->mlx_image = images->collectable_img;
				collectable_count++;
			}
			x++;
		}
		y++;
	}
	set_tile_order(map, images, floor_count);
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