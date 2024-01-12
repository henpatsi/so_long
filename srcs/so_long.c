/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 11:10:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	print_map(t_map *map)
// {
// 	ft_printf("\nCreated map:\n\n");
// 	int i = 0;
// 	while (i < map->size[1])
// 	{
// 		int j = 0;
// 		while (j < map->size[0])
// 		{
// 			ft_printf("%c", map->grid[i][j].label);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}

// 	ft_printf("\nsize: %d, %d\n", map->size[0], map->size[1]);
// 	ft_printf("player position: %d, %d\n", map->player.y, map->player.x);
// 	ft_printf("collectible count: %d\n\n", map->collectibles);
// }

int	check_args(int argc)
{
	if (argc != 2)
	{
		if (argc < 2)
			return (map_error("no map given as argument"));
		if (argc > 2)
			return (map_error("too many arguments"));
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (!check_args(argc))
		return (1);
	map = parse_map(argv[1]);
	if (map == 0)
		return (1);
	start_game(map);
	free_map(map);
	return (0);
}
