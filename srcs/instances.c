/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:20:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 10:21:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_instance_t	*get_tile(t_map *map, int x, int y)
{
	mlx_image_t	*image;
	int			instance;

	image = map->grid[y][x].tile_img;
	instance = map->grid[y][x].tile_inst;
	return (&image->instances[instance]);
}

mlx_instance_t	*get_object(t_map *map, int x, int y)
{
	mlx_image_t	*image;
	int			instance;

	image = map->grid[y][x].obj_img;
	if (image == 0)
		return (0);
	instance = map->grid[y][x].obj_inst;
	return (&image->instances[instance]);
}

mlx_instance_t	*get_player(t_map *map)
{
	return (&map->player.img->instances[map->player.inst]);
}
