/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/08 13:35:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*initialize_tile(mlx_t *mlx, int color)
{
	mlx_image_t	*tile;

	tile = mlx_new_image(mlx, TILE_WIDTH, TILE_HEIGHT);
	if (!tile)
		return (0);

	int	y = 0;
	while (y < TILE_HEIGHT)
	{
		int x = 0;
		while (x < TILE_WIDTH)
		{
			mlx_put_pixel(tile, x, y, color);
			x++;
		}
		y++;
	}
	return (tile);
}

void set_tile_order(t_map *map, mlx_image_t *coll, mlx_image_t *floor, int floor_count)
{
	int i = 0;
	while (i < floor_count)
	{
		mlx_set_instance_depth(&floor->instances[i], -20);
		i++;
	}
	i = 0;
	while (i < map->collectibles)
	{
		mlx_set_instance_depth(&coll->instances[i], 0);
		i++;
	}
	mlx_set_instance_depth(&map->player->mlx_image->instances[0], 10);
}

void place_tiles(mlx_t *mlx, t_map *map, mlx_image_t *floor, mlx_image_t *wall, mlx_image_t *exit, mlx_image_t *coll)
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
				mlx_image_to_window(mlx, floor, x * TILE_WIDTH, y * TILE_HEIGHT);
				floor_count++;
			}
			else
				mlx_image_to_window(mlx, wall, x * TILE_WIDTH, y * TILE_HEIGHT);
			if (map->grid[y][x].label == 'P')
				mlx_image_to_window(mlx, map->player->mlx_image, x * TILE_WIDTH, y * TILE_HEIGHT);
			if (map->grid[y][x].label == 'E')
				mlx_image_to_window(mlx, exit, x * TILE_WIDTH, y * TILE_HEIGHT);
			if (map->grid[y][x].label == 'C')
			{
				mlx_image_to_window(mlx, coll, x * TILE_WIDTH, y * TILE_HEIGHT);
				map->grid[y][x].object = malloc(sizeof (t_object));
				map->grid[y][x].object->instance = collectable_count;
				map->grid[y][x].object->mlx_image = coll;
				collectable_count++;
			}
			x++;
		}
		y++;
	}
	set_tile_order(map, coll, floor, floor_count);
}

int	initialize_textures(mlx_t *mlx, t_map *map)
{
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t *exit_img;
	mlx_image_t *coll_img;
	
	floor_img = initialize_tile(mlx, 0x254d1aFF);
	wall_img = initialize_tile(mlx, 0x422009FF);
	exit_img = initialize_tile(mlx, 0xFFFFFFFF);
	coll_img = initialize_tile(mlx, 0xFFFF00FF);
	if (!floor_img || !wall_img || !exit_img || !coll_img)
		return (0);
	map->player->mlx_image = initialize_tile(mlx, 0x000000FF);
	if (!map->player->mlx_image)
		return (0);

	place_tiles(mlx, map, floor_img, wall_img, exit_img, coll_img);
	
	return (1);
}