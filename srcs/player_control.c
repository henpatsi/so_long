/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:29 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 15:36:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_texture(t_map *map, int up, int right)
{
	get_player(map)->y -= up * map->tile_size;
	get_player(map)->x += right * map->tile_size;
}

void	collect_collectable(t_map *map, int x, int y)
{
	mlx_instance_t	*object;

	object = get_object(map, x, y);
	if (object == 0)
		return ;
	map->collectibles--;
	object->enabled = 0;
}

void	move_player(t_map *map, int up, int right)
{
	static int	moves;
	static int	won;
	t_gridpos	target_pos;
	t_player	*player;

	player = &map->player;
	target_pos = map->grid[player->y - up][player->x + right];
	if (target_pos.label == '1'
		|| (target_pos.label == 'E' && map->collectibles != 0))
		return ;
	if (target_pos.label == 'C')
		collect_collectable(map, player->x + right, player->y - up);
	map->grid[player->y][player->x].label = '0';
	player->y -= up;
	player->x += right;
	map->grid[player->y][player->x].label = 'P';
	moves++;
	if (won == 0)
		ft_printf("Moves: %d\n", moves);
	move_player_texture(map, up, right);
	if (target_pos.label == 'E')
	{
		ft_printf("VICTORY!\n");
		won = 1;
	}
}
