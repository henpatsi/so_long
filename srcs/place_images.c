/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:50:17 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 11:24:36 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_tile(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label != '1')
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->floor_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->tile_img = images->floor_img;
		mlx_set_instance_depth(get_tile(map, pos->x, pos->y), -20);
	}
	else
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->wall_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->tile_img = images->wall_img;
		mlx_set_instance_depth(get_tile(map, pos->x, pos->y), -20);
	}
}

void	place_object(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label == 'P')
	{
		map->player.inst = mlx_image_to_window(mlx, images->player_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		map->player.img = images->player_img;
		mlx_set_instance_depth(get_player(map), 0);
	}
	if (pos->label == 'E')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->exit_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->obj_img = images->exit_img;
		mlx_set_instance_depth(get_object(map, pos->x, pos->y), -10);
	}
	if (pos->label == 'C')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->collectable_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->obj_img = images->collectable_img;
		mlx_set_instance_depth(get_object(map, pos->x, pos->y), -10);
	}
}

void	place_images(mlx_t *mlx, t_map *map, t_images *images)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size[1])
	{
		x = 0;
		while (x < map->size[0])
		{
			place_tile(mlx, map, &map->grid[y][x], images);
			place_object(mlx, map, &map->grid[y][x], images);
			x++;
		}
		y++;
	}
}
