/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:08:29 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 16:14:38 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_texture(t_map *map, int up, int right)
{
	mlx_image_t	*image;
	int			instance;

	image = map->player.img;
	instance = map->player.inst;
	image->instances[instance].y -= up * map->tile_size;
	image->instances[instance].x += right * map->tile_size;
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
	t_gridpos	target_pos;

	target_pos = map->grid[map->player.y - up][map->player.x + right];
	if (target_pos.label == '1' || (target_pos.label == 'E' && map->collectibles != 0))
		return ;
	if (target_pos.label == 'C')
		collect_collectable(map, map->player.x + right, map->player.y - up);
	map->grid[map->player.y][map->player.x].label = '0';
	map->player.y -= up;
	map->player.x += right;
	map->grid[map->player.y][map->player.x].label = 'P';
	moves++;
	ft_printf("Moves: %d\n", moves);
	move_player_texture(map, up, right);
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
