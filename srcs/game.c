/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 11:55:32 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int	start_game(t_map *map)
{
	mlx_t		*mlx;
	t_images	images;
	int			monitor_size[2];

	mlx = mlx_init(map->size[0] * map->tile_size,
			map->size[1] * map->tile_size, "so_long", false);
	if (!mlx)
		return (game_error(map));
	if (!initialize_graphics(mlx, map, &images))
		return (game_error(map));
	map->images = images;
	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	mlx_set_window_limit(mlx, -1, -1, monitor_size[0], monitor_size[1]);
	if (map->size[0] * map->tile_size > monitor_size[0]
		|| map->size[1] * map->tile_size > monitor_size[1])
		resize(monitor_size[0], monitor_size[1], map);
	else
		resize_images(map, images, map->tile_size);
	mlx_key_hook(mlx, &player_key_hook, map);
	mlx_loop_hook(mlx, &window_input_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
