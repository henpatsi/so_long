/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:29 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 13:32:41 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_texture(t_map *map, int up, int right)
{
	map->grid[map->player_pos[0]][map->player_pos[1]].object->y -= up * TILE_HEIGHT;
	map->grid[map->player_pos[0]][map->player_pos[1]].object->x += right * TILE_WIDTH;
}

void	collect_collectable(t_map *map, mlx_instance_t *collectable)
{
	if (collectable == 0)
		return ;
	map->collectibles--;
	collectable->enabled = 0;
}

void	move_player(t_map *map, int up, int right)
{
	static int	moves;
	t_gridpos	target_pos;

	target_pos = map->grid[map->player_pos[0] - up][map->player_pos[1] + right];
	if (target_pos.label == '1' || (target_pos.label == 'E' && map->collectibles != 0))
		return ;
	if (target_pos.label == 'C')
		collect_collectable(map, target_pos.object);
	move_player_texture(map, up, right);
	map->grid[map->player_pos[0]][map->player_pos[1]].label = '0';
	map->player_pos[0] -= up;
	map->player_pos[1] += right;
	map->grid[map->player_pos[0]][map->player_pos[1]].label = 'P';
	moves++;
	ft_printf("Moves: %d\n", moves);
	if (target_pos.label == 'E')
		ft_printf("VICTORY!\n");
}

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
