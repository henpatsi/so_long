/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 09:58:14 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 12:53:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_image(mlx_instance_t *instance, int x, int y, int amount)
{
	instance->x -= x * (amount);
	instance->y -= y * (amount);
}

void	move_resized_images(t_map *map, int new_size)
{
	mlx_instance_t	*tile;
	mlx_instance_t	*object;
	int				y;
	int				x;

	y = 0;
	while (y < map->size[1])
	{
		x = 0;
		while (x < map->size[0])
		{
			tile = get_tile(map, x, y);
			move_image(tile, x, y, map->tile_size - new_size);
			object = get_object(map, x, y);
			if (object != 0)
				move_image(object, x, y, map->tile_size - new_size);
			x++;
		}
		y++;
	}
	get_player(map)->x -= map->player.x * (map->tile_size - new_size);
	get_player(map)->y -= map->player.y * (map->tile_size - new_size);
}

void	resize_images(t_map *map, t_images images, int new_size)
{
	mlx_resize_image(images.player_img, new_size, new_size);
	mlx_resize_image(images.floor_img, new_size, new_size);
	mlx_resize_image(images.wall_img, new_size, new_size);
	mlx_resize_image(images.exit_img, new_size, new_size);
	mlx_resize_image(images.collectable_img, new_size, new_size);
	move_resized_images(map, new_size);
}

void	resize(int width, int height, void *param)
{
	t_map		*map;
	int			new_size;

	map = param;
	new_size = width / map->size[0];
	if (map->size[0] * map->tile_size > width)
		new_size = width / map->size[0];
	if (map->size[1] * new_size > height)
		new_size = height / map->size[1];
	resize_images(map, map->images, new_size);
	map->tile_size = new_size;
}
