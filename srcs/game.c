/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 15:01:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42.h"

int	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	return (1);
}

void	print_grid(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i] != 0)
	{
		ft_printf("%s\n", map->grid[i]);
		i++;
	}
}

void	control_hook(mlx_key_data_t keydata, void* param)
{
	static int	moves;
	t_map		*map = param; 

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		ft_printf("W\n");
		moves++;
		ft_printf("Moves: %d\n", moves);
		map->grid[map->player[0]][map->player[1]] = '0';
		map->player[0] -= 1;
		map->grid[map->player[0]][map->player[1]] = 'P';
		ft_printf("player position: %d, %d\n", map->player[0], map->player[1]);
		print_grid(map);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		ft_printf("S\n");
		moves++;
		ft_printf("Moves: %d\n", moves);
		print_grid(map);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		ft_printf("A\n");
		moves++;
		ft_printf("Moves: %d\n", moves);
		print_grid(map);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		ft_printf("D\n");
		moves++;
		ft_printf("Moves: %d\n", moves);
		print_grid(map);
	}
}

int	start_game(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	print_grid(map);
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		return (error());
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (error());
	mlx_key_hook(mlx, &control_hook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
