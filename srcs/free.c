/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:49:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 13:18:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_map(t_map *map)
{
	free_grid(map->grid);
	free(map);
	return (0);
}

int	free_grid(t_gridpos **grid)
{
	int	i;

	i = 0;
	while (grid[i] != 0)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (0);
}

// int	free_textures(mlx_texture_t *textures[])
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < TEXTURE_COUNT)
// 	{
// 		mlx_delete_texture(textures[i]);
// 		i++;
// 	}
// 	return (0);
// }
