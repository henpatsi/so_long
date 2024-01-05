/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 14:51:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"

# ifndef WIDTH
#  define WIDTH 512
# endif
# ifndef HEIGHT
#  define HEIGHT 512
# endif

typedef struct s_map
{
	char	**grid;
	int		size[2];
	int		player[2];
	int		collectibles;
}	t_map;

int		start_game(t_map *map);

t_map	*parse_map(char	*map_file);
int		check_extension(char	*map_file);
int		check_symbols(int map_fd, int size[]);
int		check_grid(char **grid, int size[]);

int		ft_strsfree(char **strs);
int		free_map(t_map *map);
int		try_open_file(char	*file);

#endif