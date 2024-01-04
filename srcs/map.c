/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:26:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 12:35:51 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extention(char	*map_file)
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
		if (line == 0)
			return (0);
	}
	free(line);
	if (pce[0] == 0 || pce [1] == 0 || pce[2] == 0)
		return (0);
	return (1);
}

int	fill_grid(char **grid, int size[], int map_fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < size[1])
	{
		line = get_next_line(map_fd);
		if (line == 0)
		{
			ft_strsfree(grid);
			return (0);
		}
		grid[i] = ft_strtrim(line, "\n");
		free(line);
		if (grid[i] == 0)
		{
			ft_strsfree(grid);
			return (0);
		}
		i++;
	}
	grid[i] = 0;
	return (1);
}

int	check_grid(char **grid, int size[])
{
	int	i;

	i = 0;
	while (grid[0][i] != 0)
	{
		if (grid[0][i] != '1' || grid[size[1] - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

char	**parse_map(char	*map_file)
{
	char	**grid;
	int		map_fd;
	int		size[2];

	if (!check_extention(map_file))
		return (0);
	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	if (!check_symbols(map_fd, size))
		return (0);
	close(map_fd);
	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	grid = ft_calloc(size[1] + 1, sizeof(char *));
	if (!fill_grid(grid, size, map_fd))
		return (0);
	close(map_fd);
	if (!check_grid(grid, size))
		return (0);
	return (grid);
}
