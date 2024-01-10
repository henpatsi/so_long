/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 11:25:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	initialize_textures(t_textures *textures)
{
	textures->player_tex = mlx_load_png(PLAYER_TEXTURE);
	if (!textures->player_tex)
		return (0);
	textures->floor_tex = mlx_load_png(FLOOR_TEXTURE);
	if (!textures->floor_tex)
		return (0);
	textures->wall_tex = mlx_load_png(WALL_TEXTURE);
	if (!textures->wall_tex)
		return (0);
	textures->exit_tex = mlx_load_png(EXIT_TEXTURE);
	if (!textures->exit_tex)
		return (0);
	textures->collectable_tex = mlx_load_png(COLLECTABLE_TEXTURE);
	if (!textures->collectable_tex)
		return (0);
	return (1);
}

int	initialize_images(t_images *images, t_textures *textures, mlx_t *mlx)
{
	images->player_img = mlx_texture_to_image(mlx, textures->player_tex);
	if (!images->player_img)
		return (0);
	images->floor_img = mlx_texture_to_image(mlx, textures->floor_tex);
	if (!images->floor_img)
		return (0);
	images->wall_img = mlx_texture_to_image(mlx, textures->wall_tex);
	if (!images->wall_img)
		return (0);
	images->exit_img = mlx_texture_to_image(mlx, textures->exit_tex);
	if (!images->exit_img)
		return (0);
	images->collectable_img = mlx_texture_to_image(mlx,
			textures->collectable_tex);
	if (!images->collectable_img)
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
	place_images(mlx, map, images);
	return (1);
}
