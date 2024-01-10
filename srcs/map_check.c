/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:06:13 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 12:27:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_line(char	*line, int width, int pce[])
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if ((i == 0 || i == width - 1) && line[i] != '1')
			return (map_error("map is not surrounded by walls"));
		if (!ft_strchr("01PCE", line[i]))
			return (map_error("map contains an invalid character"));
		if (line[i] == 'P' && pce[0] != 0)
			return (map_error("map contains more than one starting position"));
		if (line[i] == 'E' && pce[2] != 0)
			return (map_error("map contains more than one exit"));
		if (line[i] == 'P')
			pce[0] = 1;
		if (line[i] == 'E')
			pce[2] = 1;
		if (line[i] == 'C')
			pce[1]++;
		i++;
	}
	if (i != width)
		return (map_error("map is not rectangular"));
	return (1);
}

int	check_symbols(int map_fd, int size[])
{
	char	*line;
	int		pce[3];

	line = get_next_line(map_fd);
	if (line == 0)
		return (0);
	size[0] = 0;
	while (line[size[0]] != '\n' && line[size[0]] != '\0')
		size[0]++;
	ft_bzero(pce, 3 * sizeof(int));
	size[1] = 0;
	while (line != 0)
	{
		if (!check_line(line, size[0], pce))
		{
			free(line);
			return (0);
		}
		size[1]++;
		free(line);
		line = get_next_line(map_fd);
	}
	if (pce[0] == 0 || pce [1] == 0 || pce[2] == 0)
		return (map_error("map is missing a required character"));
	return (1);
}

int	find_path(t_gridpos **grid, int i, int j)
{
	char	symbol;

	if (grid[i] == 0 || grid[i][j].label == 0)
		return (0);
	symbol = grid[i][j].label;
	if (symbol == '1' || symbol == 'X')
		return (0);
	if (symbol == 'E')
		return (1);
	grid[i][j].label = 'X';
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
	grid[i][j].label = symbol;
	return (0);
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
	return (1);
}
