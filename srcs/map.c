/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:26:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 14:23:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill_grid(char **grid, int size[], int map_fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < size[1])
	{
		line = get_next_line(map_fd);
		if (line == 0)
			return (0);
		grid[i] = ft_strtrim(line, "\n");
		free(line);
		if (grid[i] == 0)
			return (0);
		i++;
	}
	grid[i] = 0;
	return (1);
}

char	**parse_map(char	*map_file)
{
	char	**grid;
	int		map_fd;
	int		size[2];

	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	if (!check_extension(map_file) || !check_symbols(map_fd, size))
	{
		close(map_fd);
		return (0);
	}
	close(map_fd);
	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	grid = ft_calloc(size[1] + 1, sizeof(char *));
	if (grid == 0)
	{
		close(map_fd);
		return (0);
	}
	if (!fill_grid(grid, size, map_fd) || !check_grid(grid, size))
	{
		ft_strsfree(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	return (grid);
}
