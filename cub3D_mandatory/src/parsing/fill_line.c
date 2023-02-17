/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:00:03 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:00:03 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	fill_first_line(char **map, char **new_map)
{
	int	j;

	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		new_map[0][j] = '1';
		j++;
	}
}

void	fill_first_space_line(char **map, char **new_map)
{
	int	j;

	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		if (j == 0 || j == ft_find_big_line(map) + 2)
			new_map[1][j] = '1';
		else
			new_map[1][j] = ' ';
		j++;
	}
}

void	fill_last_line(char **map, char **new_map)
{
	int	j;

	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		new_map[ft_map_length(map) + 3][j] = '1';
		j++;
	}
}

void	fill_last_space_line(char **map, char **new_map)
{
	int	j;

	j = 0;
	while (j <= ft_find_big_line(map) + 2)
	{
		if (j == 0 || j == ft_find_big_line(map) + 2)
			new_map[ft_map_length(map) + 2][j] = '1';
		else
			new_map[ft_map_length(map) + 2][j] = ' ';
		j++;
	}
}

void	fill_line_border(char **map, char **new_map)
{
	int	i;

	i = 2;
	while (i <= ft_map_length(map) + 1)
	{
		new_map[i][0] = '1';
		new_map[i][1] = ' ';
		new_map[i][ft_find_big_line(map) + 2] = '1';
		new_map[i][ft_find_big_line(map) + 1] = ' ';
		i++;
	}
}
