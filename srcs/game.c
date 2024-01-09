/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 11:54:09 by hpatsi           ###   ########.fr       */
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

// TODO
void	resize_hook(int width, int height, void* param)
{
	if (param == NULL)
		return ;
	width += 1;
	height += 1;
}

int	start_game(t_map *map)
{
	mlx_t	*mlx;
	int		monitor_size[2];

	mlx = mlx_init(map->size[0] * TILE_WIDTH, map->size[1] * TILE_HEIGHT, "so_long", true);
	if (!mlx)
		return (error(map));

	if (!initialize_graphics(mlx, map))
		return (error(map));

	mlx_resize_hook(mlx, &resize_hook, NULL);

	mlx_get_monitor_size(0, &monitor_size[0], &monitor_size[1]);
	mlx_set_window_limit(mlx, -1, -1, monitor_size[0], monitor_size[1]);

	mlx_key_hook(mlx, &player_key_hook, map);
	mlx_loop_hook(mlx, &window_input_hook, mlx);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
