/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 16:48:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	place_tile(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
{
	if (pos->label != '1')
		pos->tile_inst = mlx_image_to_window(mlx, images->floor_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
	else
		pos->tile_inst = mlx_image_to_window(mlx, images->wall_img,
				pos->x * map->tile_size, pos->y * map->tile_size);
	if (pos->tile_inst == -1)
			return (0);
	if (pos->label != '1')
		pos->tile_img = images->floor_img;
	else
		pos->tile_img = images->wall_img;
	mlx_set_instance_depth(get_tile(map, pos->x, pos->y), -20);
	return(1);
}

int	place_object(mlx_t *mlx, t_map *map, t_gridpos *pos, t_images *images)
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
	return(1);
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
			x++;
		}
		y++;
	}
	return(1);
}

mlx_image_t	*initialize_image(mlx_t *mlx, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(file);
	if (texture == 0)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

int	initialize_images(mlx_t *mlx, t_map *map)
{
	map->images.player_img = initialize_image(mlx, PLAYER_TEXTURE);
	map->images.floor_img = initialize_image(mlx, FLOOR_TEXTURE);
	map->images.wall_img = initialize_image(mlx, WALL_TEXTURE);
	map->images.exit_img = initialize_image(mlx, EXIT_TEXTURE);
	map->images.collectable_img = initialize_image(mlx, COLLECTABLE_TEXTURE);
	if (!map->images.player_img || !map->images.floor_img
		|| !map->images.wall_img || !map->images.exit_img
		|| !map->images.collectable_img)
		return (0);
	if (resize_images(map->images, map->tile_size) == 0)
		return (0);
	if (place_images(mlx, map, &map->images) == 0)
		return (0);
	return (1);
}
