/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:33:35 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/17 10:10:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	initialize_player_animations(mlx_t *mlx, t_map *map)
{
	int		i;
	char	*files[4];

	files[0] = PLAYER_ANIM_0;
	files[1] = PLAYER_ANIM_1;
	files[2] = PLAYER_ANIM_2;
	files[3] = PLAYER_ANIM_3;
	i = 0;
	while (i < 4)
	{
		map->player_anims[i] = initialize_image(mlx, files[i]);
		if (map->player_anims[i] == 0)
			return (0);
		i++;
	}
	return (1);
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
	if (initialize_player_animations(mlx, map) == 0)
		return (0);
	if (resize_player_animations(map->player_anims, map->tile_size) == 0)
		return (0);
	return (1);
}
