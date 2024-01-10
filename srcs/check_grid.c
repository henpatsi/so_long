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
	if (symbol == 'E')
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

int	check_grid(t_gridpos **grid, int size[], int player_pos[], int *coll)
{
	int	i;
	int	j;

	i = 0;
	while (i < size[1])
	{
		j = 0;
		while (j < size[0])
		{
			if (i == 0 || i == size[1] - 1)
			{
				if (grid[i][j].label != '1')
					return (map_error("map is not surrounded by walls"));
			}
			if (grid[i][j].label == 'P')
			{
				player_pos[0] = i;
				player_pos[1] = j;
				if (!find_path(grid, i, j))
					return (map_error("no valid path to exit"));
			}
			if (grid[i][j].label == 'C')
				*coll += 1;
			j++;
		}
		i++;
	}
	clean_grid(grid, size);
	return (1);
}
