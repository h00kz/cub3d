/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:03:59 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:04:00 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	ft_check_map_close(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (map[i + 1][j] == '0')
					return (0);
				if (map[i - 1][j] == '0')
					return (0);
				if (map[i][j + 1] == '0')
					return (0);
				if (map[i][j - 1] == '0')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_calloc_map(char **map)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc(sizeof(char *), (ft_map_length(map) + 5));
	while (i < (ft_map_length(map) + 4))
	{
		new_map[i] = ft_calloc(sizeof(char), ft_find_big_line(map) + 4);
		i++;
	}
	return (new_map);
}

void	fill_tab(char **map, char **new_map)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 2;
	k = 0;
	while (map[k])
	{
		l = 0;
		j = 2;
		while (new_map[i][j] != '1')
		{
			if (j - 2 >= (int)ft_strlen(map[k]) || map[k][j - 2] == '\n')
				new_map[i][j++] = ' ';
			else
				new_map[i][j++] = map[k][l++];
		}
		i++;
		k++;
	}
}

char	**ft_verif_map(char **map)
{	
	int		i;
	char	**new_map;

	i = -1;
	new_map = ft_calloc_map(map);
	fill_first_line(map, new_map);
	fill_first_space_line(map, new_map);
	fill_last_line(map, new_map);
	fill_last_space_line(map, new_map);
	fill_line_border(map, new_map);
	fill_tab(map, new_map);
	while (map[++i])
		free(map[i]);
	free(map);
	if (ft_check_map_close(new_map) == 0)
	{
		i = 0;
		while (new_map[i])
			free(new_map[i++]);
		free(new_map);
		new_map = NULL;
	}
	return (new_map);
}
