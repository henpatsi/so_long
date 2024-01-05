/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 16:13:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_map *map)
{
	int	i;

	ft_printf("\nCreated map:\n\n");
	i = 0;
	while (map->grid[i] != 0)
	{
		ft_printf("%s\n", map->grid[i]);
		i++;
	}

	ft_printf("\nsize: %d, %d\n", map->size[0], map->size[1]);
	ft_printf("player position: %d, %d\n", map->player[0], map->player[1]);
	ft_printf("collectible count: %d\n\n", map->collectibles);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc < 2)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (1);
	}
	map = parse_map(argv[1]);
	if (map == 0)
	{
		ft_putstr_fd("Error\n", 2); // TODO explicit errors
		return (1);
	}
	print_map(map);
	start_game(map);
	free_map(map);
	return (0);
}
