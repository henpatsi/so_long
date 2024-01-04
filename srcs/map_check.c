/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:06:13 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 14:28:38 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extension(char	*map_file)
{
	char	*extn;

	extn = ft_strrchr(map_file, '.');
	if (extn == 0)
		return (0);
	return (ft_strcmp(extn, ".ber") == 0);
}

int	check_line(char	*line, int width, int pce[])
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if ((i == 0 || i == width - 1) && line[i] != '1')
			return (0);
		if (!ft_strchr("01PCE", line[i]))
			return (0);
		if ((line[i] == 'P' && pce[0] != 0) || (line[i] == 'E' && pce[2] != 0))
			return (0);
		if (line[i] == 'P')
			pce[0] = 1;
		if (line[i] == 'E')
			pce[2] = 1;
		if (line[i] == 'C')
			pce[1]++;
		i++;
	}
	if (i != width)
		return (0);
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
		return (0);
	return (1);
}

int	find_path(char **grid, int i, int j)
{
	char	symbol;

	if (grid[i] == 0 || grid[i][j] == 0)
		return (0);
	symbol = grid[i][j];
	if (symbol == '1' || symbol == 'X')
		return (0);
	if (symbol == 'E')
		return (1);
	grid[i][j] = 'X';
	if (find_path(grid, i + 1, j) == 1 || find_path(grid, i - 1, j) == 1)
	{
		grid[i][j] = symbol;
		return (1);
	}
	if (find_path(grid, i, j + 1) == 1 || find_path(grid, i, j - 1) == 1)
	{
		grid[i][j] = symbol;
		return (1);
	}
	grid[i][j] = symbol;
	return (0);
}

int	check_grid(char **grid, int size[])
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != 0)
	{
		j = 0;
		while (grid[i][j] != 0)
		{
			if (i == 0 || i == size[1] - 1)
			{
				if (grid[i][j] != '1')
					return (0);
			}
			if (grid[i][j] == 'P')
			{
				if (!find_path(grid, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
