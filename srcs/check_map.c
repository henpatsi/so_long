/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:06:13 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/10 18:08:46 by hpatsi           ###   ########.fr       */
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
	return (pce[1]);
}

int	check_map(char	*map_file, int size[])
{
	int		map_fd;
	char	*extn;
	int		collectibles;

	map_fd = try_open_file(map_file);
	if (map_fd == -1)
		return (0);
	extn = ft_strrchr(map_file, '.');
	if (extn == 0)
		return (0);
	if (ft_strcmp(extn, ".ber") != 0)
		return (map_error("map does not end with a .ber extention"));
	collectibles = check_symbols(map_fd, size);
	close(map_fd);
	if (!collectibles)
		return (0);
	return (collectibles);
}