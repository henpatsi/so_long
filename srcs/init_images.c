/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 14:05:30 by hpatsi           ###   ########.fr       */
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

int	initialize_images(mlx_t *mlx, t_images *images)
{
	images->player_img = initialize_image(mlx, PLAYER_TEXTURE);
	images->floor_img = initialize_image(mlx, FLOOR_TEXTURE);
	images->wall_img = initialize_image(mlx, WALL_TEXTURE);
	images->exit_img = initialize_image(mlx, EXIT_TEXTURE);
	images->collectable_img = initialize_image(mlx, COLLECTABLE_TEXTURE);
	if (!images->player_img || !images->floor_img || !images->wall_img
		|| !images->exit_img || !images->collectable_img)
		return (0);
	return (1);
}

int	initialize_graphics(mlx_t *mlx, t_map *map)
{
	if (!initialize_images(mlx, &map->images))
		return (0);
	resize_images(map->images, map->tile_size);
	place_images(mlx, map, &map->images);
	return (1);
}
