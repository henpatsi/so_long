/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:28:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/08 14:13:06 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_map(t_map *map)
{
	free(map);
	return (0);
}

int	try_open_file(char	*file)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
		perror(file);
	return (file_fd);
}
