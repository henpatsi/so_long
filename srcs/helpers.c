/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:28:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 16:34:34 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_map(t_map *map)
{
	free(map);
	return (0);
}

int	try_open_file(char	*file)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		perror(file);
	return (file_fd);
}

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
