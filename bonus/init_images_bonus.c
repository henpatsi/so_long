/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 10:21:38 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*initialize_image(mlx_t *mlx, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(file);
	if (texture == 0)
		return (0);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

int	initialize_images(mlx_t *mlx, t_map *map)
{
	map->images.player_img = initialize_image(mlx, PLAYER_TEXTURE);
	map->images.floor_img = initialize_image(mlx, FLOOR_TEXTURE);
	map->images.wall_img = initialize_image(mlx, WALL_TEXTURE);
	map->images.exit_img = initialize_image(mlx, EXIT_TEXTURE);
	map->images.collectable_img = initialize_image(mlx, COLLECTABLE_TEXTURE);
	if (!map->images.player_img || !map->images.floor_img
		|| !map->images.wall_img || !map->images.exit_img
		|| !map->images.collectable_img)
		return (0);
	if (resize_images(map->images, map->tile_size) == 0)
		return (0);
	if (place_images(mlx, map, &map->images) == 0)
		return (0);
	return (1);
}
