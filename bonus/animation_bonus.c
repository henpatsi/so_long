/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:50:09 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 14:59:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	animate_player(t_map *map)
{
	static int	anim_i;
	mlx_image_t	*player_img;
	mlx_image_t	*anim_img;

	anim_i++;
	if (anim_i > 3)
		anim_i = 0;
	player_img = map->player.img;
	anim_img = map->player_anims[anim_i];
	ft_memcpy(player_img->pixels, anim_img->pixels,
		player_img->width * player_img->height * sizeof(int32_t));
}