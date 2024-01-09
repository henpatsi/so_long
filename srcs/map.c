/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:26:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/09 16:59:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*initialize_map(t_gridpos **grid, int size[], int p_pos[], int collectibles)
{
	t_map		*map;

	map = malloc(sizeof(t_map));
	if (map == 0)
		return (0);
	map->grid = grid;
	map->size[0] = size[0];
	map->size[1] = size[1];
	map->collectibles = collectibles;
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
		grid[i] = ft_calloc(size[0], sizeof(t_gridpos));
		if (grid[i] == 0)
			return (0);
		while(line[j] != 0 && line[j] != '\n')
		{
			grid[i][j].label = line[j];
			j++;
		}
		free(line);
		i++;
	}
	return (1);
}

t_gridpos	**create_grid(char	*map_file, int size[], int player_pos[], int *collectibles)
{
	int			map_fd;
	t_gridpos	**grid;

	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	grid = ft_calloc(size[1], sizeof(t_gridpos *));
	if (grid == 0)
	{
		close(map_fd);
		return (0);
	}
	if (!fill_grid(grid, size, map_fd) || !check_grid(grid, size, player_pos, collectibles))
	{
		// ft_strsfree(grid);
		close(map_fd);
		return (0);
	}
	close(map_fd);
	return (grid);
}

t_map	*parse_map(char	*map_file)
{
	int			map_fd;
	int			size[2];
	t_gridpos	**grid;
	int 		player_pos[2];
	int 		collectibles;

	map_fd = try_open_file(map_file);
	if (map_fd == -1)
	{
		ft_printf("could not open file\n");
		return (0);
	}
	if (!check_extension(map_file) || !check_symbols(map_fd, size))
	{
		close(map_fd);
		return (0);
	}
	close(map_fd);
	collectibles = 0;
	grid = create_grid(map_file, size, player_pos, &collectibles);
	if (grid == 0)
		return (0);
	return (initialize_map(grid, size, player_pos, collectibles));
}
