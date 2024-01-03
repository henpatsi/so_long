/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:26:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/03 16:59:22 by hpatsi           ###   ########.fr       */
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

int	check_map(int map_fd, int size[2])
{
	char	*line;

	line = get_next_line(map_fd);
	size[0] = 0;
	size[1] = 1;
	return (1);
}

char	**parse_map(char	*map_file)
{
	char	**grid;
	int		map_fd;
	int		size[2];

	if (!check_extension(map_file))
		return (0);
	map_fd = open(map_file, O_RDONLY);
	if (map_fd == -1)
	{
		perror(map_file);
		return (0);
	}
	if (!check_map(map_fd, size))
		return (0);

	grid = ft_calloc(1, 1);
	return (grid);
}