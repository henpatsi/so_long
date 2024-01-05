/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:42:27 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 13:10:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42.h"

int	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	return (1);
}

void	print_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != 0)
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
}

int	start_game(char **grid)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	print_grid(grid);
	mlx = mlx_init(512, 512, "so_long", true);
	if (!mlx)
		return (error());
	img = mlx_new_image(mlx, 512, 512);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (error());
	int x = 0;
	while (x < 512)
	{
		mlx_put_pixel(img, x, x, 0xFF0000FF);
		x++;
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
