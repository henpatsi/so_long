/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/12 14:54:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_args(int argc)
{
	if (argc != 2)
	{
		if (argc < 2)
			return (map_error("no map given as argument"));
		if (argc > 2)
			return (map_error("too many arguments"));
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (!check_args(argc))
		return (1);
	map = parse_map(argv[1]);
	if (map == 0)
		return (1);
	start_game(map);
	free_map(map);
	return (0);
}
