/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:02:18 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 18:02:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_path(t_gridpos **grid, int i, int j)
{
	char	symbol;

	if (grid[i] == 0 || grid[i][j].label == 0)
		return (0);
	symbol = grid[i][j].label;
	if (symbol == '1' || symbol == 'X' || symbol == 'Y')
		return (0);
	if (symbol == 'P')
		return (1);
	if (symbol == '0')
		grid[i][j].label = 'X';
	if (symbol == 'C')
		grid[i][j].label = 'Y';
	if (find_path(grid, i + 1, j) == 1 || find_path(grid, i - 1, j) == 1)
	{
		grid[i][j].label = symbol;
		return (1);
	}
	if (find_path(grid, i, j + 1) == 1 || find_path(grid, i, j - 1) == 1)
	{
		grid[i][j].label = symbol;
		return (1);
	}
	return (0);
}

void	clean_grid(t_gridpos **grid, int size[])
{
	int	i;
	int	j;

	i = 0;
	while (i < size[1])
	{
		j = 0;
		while (j < size[0])
		{
			if (grid[i][j].label == 'X')
				grid[i][j].label = '0';
			if (grid[i][j].label == 'Y')
				grid[i][j].label = 'C';
			j++;
		}
		i++;
	}
}

int	check_walls(t_gridpos **grid, int size[], int x, int y)
{
	if (y == 0 || y == size[1] - 1)
	{
		if (grid[y][x].label != '1')
			return (map_error("map is not surrounded by walls"));
	}
	return (1);
}

int	check_paths(t_gridpos **grid, int size[], int x, int y)
{
	if (grid[y][x].label == 'E' || grid[y][x].label == 'C')
	{
		if (!find_path(grid, y, x))
			return (map_error("no valid path to exit"));
		clean_grid(grid, size);
	}
	return (1);
}

int	check_grid(t_gridpos **grid, int size[], t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < size[1])
	{
		x = 0;
		while (x < size[0])
		{
			if (!check_walls(grid, size, x, y))
				return (0);
			if (!check_paths(grid, size, x, y))
				return (0);
			if (grid[y][x].label == 'P')
			{
				player->x = x;
				player->y = y;
			}
			x++;
		}
		y++;
	}
	return (1);
}
