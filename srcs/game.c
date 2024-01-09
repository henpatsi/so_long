/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 10:06:42 by hpatsi           ###   ########.fr       */
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

int	start_game(t_map *map)
{
	mlx_t		*mlx;

	mlx = mlx_init(map->size[0] * TILE_WIDTH, map->size[1] * TILE_HEIGHT, "so_long", true);
	if (!mlx)
		return (error(map));

	if (!initialize_graphics(mlx, map))
		return (error(map));

	mlx_key_hook(mlx, &player_key_hook, map);
	mlx_loop_hook(mlx, &window_input_hook, mlx);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
