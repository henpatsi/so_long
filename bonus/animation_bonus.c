/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:50:09 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/16 13:29:10 by hpatsi           ###   ########.fr       */
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
	if (anim_i == 0)
		anim_img = map->player_anims.player_anim0;
	else if (anim_i == 1)
		anim_img = map->player_anims.player_anim1;
	else if (anim_i == 2)
		anim_img = map->player_anims.player_anim2;
	else
		anim_img = map->player_anims.player_anim3;
	ft_memcpy(player_img->pixels, anim_img->pixels, 
		player_img->width * player_img->height * sizeof(int32_t));
}