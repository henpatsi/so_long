/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 14:06:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	player_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(map, 1, 0);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(map, -1, 0);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(map, 0, -1);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(map, 0, 1);
}

void	window_input_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

void	anim_update_hook(void *param)
{
	static double	timer;
	t_map			*map;
	mlx_t			*mlx;

	map = param;
	mlx = map->mlx;
	timer += mlx->delta_time;
	if (timer < (double) ANIM_DELAY)
		return ;
	timer = 0;
	map = param;
	animate_player(map);
}

int	start_game(t_map *map) 
{
	mlx_t	*mlx;

	mlx = mlx_init(map->size[0] * map->tile_size,
			map->size[1] * map->tile_size, "so_long", false);
	if (mlx == 0)
		return (game_error(mlx, map));
	map->mlx = mlx;
	limit_to_monitor_size(mlx, map);
	if (initialize_images(mlx, map) == 0)
		return (game_error(mlx, map));
	mlx_key_hook(mlx, &player_key_hook, map);
	if (mlx_loop_hook(mlx, &window_input_hook, mlx) == 0)
		return (game_error(mlx, map));
	if (mlx_loop_hook(mlx, &anim_update_hook, map) == 0)
		return (game_error(mlx, map));
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
