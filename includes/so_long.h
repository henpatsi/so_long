/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 14:21:59 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"

char	**parse_map(char	*map_file);

int		check_extension(char	*map_file);
int		check_line(char	*line, int width, int pce[]);
int		check_symbols(int map_fd, int size[]);
int		check_grid(char **grid, int size[]);

int		ft_strsfree(char **strs);
int		try_open_file(char	*file);

#endif