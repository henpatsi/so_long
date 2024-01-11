/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:26:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 18:08:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*initialize_map(t_gridpos **grid, int size[], int p_pos[], int coll)
{
	t_map		*map;

	map = malloc(sizeof(t_map));
	if (map == 0)
		return (0);
	map->grid = grid;
	map->size[0] = size[0];
	map->size[1] = size[1];
	map->collectibles = coll;
	map->player.y = p_pos[0];
	map->player.x = p_pos[1];
	map->tile_size = TILE_SIZE;
	return (map);
}

int	fill_grid(t_gridpos **grid, int size[], int map_fd)
{
	int			i;
	int			j;
	char		*line;

	i = 0;
	while (i < size[1])
	{
		line = get_next_line(map_fd);
		if (line == 0)
			return (0);
		j = 0;
		grid[i] = ft_calloc(size[0] + 1, sizeof(t_gridpos));
		if (grid[i] == 0)
			return (0);
		while (line[j] != 0 && line[j] != '\n')
		{
			grid[i][j].x = j;
			grid[i][j].y = i;
			grid[i][j].label = line[j];
			j++;
		}
		free(line);
		i++;
	}
	return (1);
}

t_gridpos	**create_grid(char	*map_file, int size[], int p_pos[])
{
	int			map_fd;
	t_gridpos	**grid;

	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	grid = ft_calloc(size[1] + 1, sizeof(t_gridpos *));
	if (grid == 0)
	{
		close(map_fd);
		return (0);
	}
	if (!fill_grid(grid, size, map_fd) || !check_grid(grid, size, p_pos))
	{
		free_grid(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	return (grid);
}

t_map	*parse_map(char	*map_file)
{
	int			size[2];
	t_gridpos	**grid;
	int			player_pos[2];
	int			collectibles;

	collectibles = check_map(map_file, size);
	if (!collectibles)
		return (0);
	grid = create_grid(map_file, size, player_pos);
	if (grid == 0)
		return (0);
	return (initialize_map(grid, size, player_pos, collectibles));
}
