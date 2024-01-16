/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_images_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:37:16 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 12:16:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	place_tile(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label != '1')
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->floor_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->tile_img = images->floor_img;
	}
	else
	{
		pos->tile_inst = mlx_image_to_window(mlx, images->wall_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->tile_img = images->wall_img;
	}
	if (pos->tile_inst == -1)
			return (0);
	mlx_set_instance_depth(get_tile(map, pos->x, pos->y), -20);
	return(1);
}

int	place_object(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label != 'E' && pos->label != 'C')
		return (1);
	if (pos->label == 'E')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->exit_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->obj_img = images->exit_img;
	}
	else if (pos->label == 'C')
	{
		pos->obj_inst = mlx_image_to_window(mlx, images->collectable_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
		pos->obj_img = images->collectable_img;
	}
	if (pos->obj_inst == -1)
			return (0);
	mlx_set_instance_depth(get_object(map, pos->x, pos->y), -10);
	return (1);
}

int	place_player(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label != 'P')
		return (1);
	map->player.inst = mlx_image_to_window(mlx, images->player_img,
		pos->x * map->tile_size, pos->y * map->tile_size);
	map->player.img = images->player_img;
	if (map->player.inst == -1)
			return (0);
	mlx_set_instance_depth(get_player(map), 0);
	return (1);
}

int	place_images(mlx_t *mlx, t_map *map, t_images *images)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size[1])
	{
		x = 0;
		while (x < map->size[0])
		{
			if (place_tile(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_object(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			if (place_player(mlx, map, &map->grid[y][x], images) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return(1);
}