/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:29 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/08 12:54:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	print_grid(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (map->grid[i] != 0)
// 	{
// 		ft_printf("%s\n", map->grid[i]);
// 		i++;
// 	}
// 	ft_printf("\n");
// }

void	move_player_texture(t_map *map, int up, int right)
{
	map->player->mlx_image->instances[0].y -= up * TILE_HEIGHT;
	map->player->mlx_image->instances[0].x += right * TILE_WIDTH;
}

void	move_player(t_map *map, int up, int right)
{
	static int	moves;
	char		target_square;

	target_square = map->grid[map->player_pos[0] - up][map->player_pos[1] + right].label;
	if (target_square == '1' || (target_square == 'E' && map->collectibles != 0))
		return ;
	if (target_square == 'C')
	{
		map->collectibles--;
		ft_printf("Collectibles left: %d\n", map->collectibles);
	}
	map->grid[map->player_pos[0]][map->player_pos[1]].label = '0';
	map->player_pos[0] -= up;
	map->player_pos[1] += right;
	map->grid[map->player_pos[0]][map->player_pos[1]].label = 'P';
	moves++;
	ft_printf("Moves: %d\n", moves);
	move_player_texture(map, up, right);
	if (target_square == 'E')
		ft_printf("VICTORY!\n");
	// print_grid(map);
}

void	player_key_hook(mlx_key_data_t keydata, void* param)
{
	t_map		*map = param;

	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(map, 1, 0);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(map, -1, 0);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(map, 0, -1);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(map, 0, 1);
}