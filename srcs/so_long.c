/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 14:23:41 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != 0)
	{
		ft_printf("%s\n", grid[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**grid;

	if (argc < 2)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (1);
	}
	grid = parse_map(argv[1]);
	if (grid == 0)
	{
		ft_putstr_fd("Error\n", 2); // TODO explicit errors
		return (1);
	}
	print_grid(grid);
	ft_strsfree(grid);
	return (0);
}
