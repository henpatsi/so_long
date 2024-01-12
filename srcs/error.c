/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:47:13 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 14:23:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	try_open_file(char	*file)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		perror(file);
	}
	return (file_fd);
}

int	game_error(mlx_t *mlx, t_map *map)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	ft_putstr_fd("\n", 2);
	free_map(map);
	if (mlx != 0)
		mlx_terminate(mlx);
	exit (1);
}

int	map_error(char *error_message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
