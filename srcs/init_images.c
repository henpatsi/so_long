/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 13:21:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialize_textures(t_textures *textures)
{
	textures->player_tex = mlx_load_png(PLAYER_TEXTURE);
	textures->floor_tex = mlx_load_png(FLOOR_TEXTURE);
	textures->wall_tex = mlx_load_png(WALL_TEXTURE);
	textures->exit_tex = mlx_load_png(EXIT_TEXTURE);
	textures->collectable_tex = mlx_load_png(COLLECTABLE_TEXTURE);
	if (!textures->player_tex || !textures->floor_tex
		|| !textures->wall_tex || !textures->exit_tex
		|| !textures->collectable_tex)
		return (0);
	return (1);
}

int	initialize_images(t_images *images, t_textures *textures, mlx_t *mlx)
{
	images->player_img = mlx_texture_to_image(mlx, textures->player_tex);
	images->floor_img = mlx_texture_to_image(mlx, textures->floor_tex);
	images->wall_img = mlx_texture_to_image(mlx, textures->wall_tex);
	images->exit_img = mlx_texture_to_image(mlx, textures->exit_tex);
	images->collectable_img = mlx_texture_to_image(mlx,
			textures->collectable_tex);
	if (!images->player_img || !images->floor_img
		|| !images->wall_img || !images->exit_img
		|| !images->collectable_img)
		return (0);
	return (1);
}

int	initialize_graphics(mlx_t *mlx, t_map *map, t_images *images)
{
	t_textures	textures;

	if (!initialize_textures(&textures))
		return (0);
	if (!initialize_images(images, &textures, mlx))
		return (0);
	resize_images(map->images, map->tile_size);
	place_images(mlx, map, images);
	return (1);
}
