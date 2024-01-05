/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 16:49:03 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(t_map *map)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	free_map(map);
	exit (1);
}

int	start_game(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*square;

	mlx = mlx_init(map->size[0] * 100, map->size[1] * 100, "so_long", true);
	if (!mlx)
		return (error(map));

	square = mlx_new_image(mlx, 100, 100);
	if (!square)
		return (error(map));

	// FILL SQUARE WITH IMAGE
	int	y = 0;
	while (y < 100)
	{
		int x = 0;
		while (x < 100)
		{
			mlx_put_pixel(square, x, y, (x + y) * 0xFF0000FF);
			x++;
		}
		y++;
	}

	// TILE SQUARE ONTO MAP
	int	i = 0;
	while (i < 100 * map->size[1])
	{
		int j = 0;
		while (j < 100 * map->size[0])
		{
			mlx_image_to_window(mlx, square, i, j);
			j += 100;
		}
		i += 100;
	}

	mlx_key_hook(mlx, &key_hook, map);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
