/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 20:09:53 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(t_map *map)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	free_map(map);
	exit (1);
}

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

void	move_resized_images(t_map *map, int new_size)
{
	mlx_instance_t	*tile;
	mlx_instance_t	*object;

	int y = 0;
	while (y < map->size[1])
	{
		int x = 0;
		while (x < map->size[0])
		{
			tile = get_tile(map, x, y);
			tile->x -= x * (map->tile_size - new_size);
			tile->y -= y * (map->tile_size - new_size);
			object = get_object(map, x, y);
			if (object != 0)
			{
				object->x -= x * (map->tile_size - new_size);
				object->y -= y * (map->tile_size - new_size);
			}
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
	map->tile_size = new_size;
}

void	resize_hook(int width, int height, void* param)
{
	t_map	*map;
	int		new_size;

	map = param;
	if (map->size[0] > map->size[1])
		new_size = width / map->size[0];
	else
		new_size = height / map->size[1];
	ft_printf("new size = %d\n", new_size);
	resize_images(map, map->images, new_size);
}

int	start_game(t_map *map)
{
	mlx_t		*mlx;
	t_images	images;
	int		monitor_size[2];

	mlx = mlx_init(map->size[0] * map->tile_size, map->size[1] * map->tile_size, "so_long", true);
	if (!mlx)
		return (error(map));
	if (!initialize_graphics(mlx, map, &images))
		return (error(map));
	map->images = images;
	resize_images(map, images, map->tile_size);
	mlx_resize_hook(mlx, &resize_hook, map);
	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	mlx_set_window_limit(mlx, -1, -1, monitor_size[0], monitor_size[1]);
	mlx_key_hook(mlx, &player_key_hook, map);
	mlx_loop_hook(mlx, &window_input_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
