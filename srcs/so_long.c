/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:12:38 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/05 13:10:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**grid;

	if (argc < 2)
	{
		ft_putstr_fd("not enough arguments\n", 2);
		return (1);
	}
	grid = parse_map(argv[1]);
	if (grid == 0)
	{
		ft_putstr_fd("Error\n", 2); // TODO explicit errors
		return (1);
	}
	start_game(grid);
	ft_strsfree(grid);
	return (0);
}
