/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 14:18:08 by hpatsi           ###   ########.fr       */
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

void	resize_move_images(t_map *map, t_images images, int new_size)
{
	mlx_resize_image(images.player_img, new_size, new_size);
	mlx_resize_image(images.floor_img, new_size, new_size);
	mlx_resize_image(images.wall_img, new_size, new_size);
	mlx_resize_image(images.exit_img, new_size, new_size);
	mlx_resize_image(images.collectable_img, new_size, new_size);

	map->tile_size = new_size;

	int y = 0;
	while (y < map->size[1])
	{
		int x = 0;
		while (x < map->size[0])
		{
			map->grid[y][x].tile->x = x * map->tile_size;
			map->grid[y][x].tile->y = y * map->tile_size;
		}
	}
}

// void	resize_hook(int width, int height, void* param)
// {
// 	mlx_resize_image(param->floor_img, )
// }

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

	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	mlx_set_window_limit(mlx, -1, -1, monitor_size[0], monitor_size[1]);

	resize_move_images(map, images, 50);

	// mlx_resize_hook(mlx, &resize_hook, images);

	mlx_key_hook(mlx, &player_key_hook, map);
	mlx_loop_hook(mlx, &window_input_hook, mlx);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
