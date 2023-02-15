/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:16 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 19:50:19 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->wall_texture = malloc(sizeof(t_wall) * 1);
	map->wall_texture->S = ft_calloc(sizeof(t_texture), 1);
	map->wall_texture->N = ft_calloc(sizeof(t_texture), 1);
	map->wall_texture->E = ft_calloc(sizeof(t_texture), 1);
	map->wall_texture->W = ft_calloc(sizeof(t_texture), 1);
	map->map = ft_calloc(sizeof(char), 1);
	map->floor = ft_calloc(sizeof(t_color), 1);
	map->cell = ft_calloc(sizeof(t_color), 1);
	return (map);
}

int	get_collision(t_game *game, t_vec pos)
{
	int	map_x_idx;
	int	map_y_idx;

	if (pos.x < 0 || pos.x > game->map->width * (MAP_TILE) || \
		pos.y < 0 || pos.y > game->map->height * (MAP_TILE))
		return (TRUE);
	map_x_idx = floor(pos.x / (MAP_TILE));
	map_y_idx = floor(pos.y / (MAP_TILE));
	return (game->map->map[map_y_idx][map_x_idx] != '1');
}

int	is_in_map(t_game *game, t_vec pos)
{
	return (pos.x >= 0 && pos.x < game->map->width * MAP_TILE && \
			pos.y >= 0 && pos.y < game->map->height * MAP_TILE);
}

void	render_minimap(t_game *game)
{
	int	x;
	int y;
	int tilec;
	int tilex = 0;
	int tiley = 0;

	y = ((int)(game->player->position->y) / MAP_TILE) - 3;
	while (y < ((int)(game->player->position->y) / MAP_TILE) + 4)
	{
		tilex = 0;
		x = ((int)(game->player->position->x) / MAP_TILE) - 3;
		while (x < ((int)(game->player->position->x) / MAP_TILE) + 4)
		{
			if (y > 0 && x > 0 && y < game->map->height && x < game->map->width && game->map->map[y][x] != '1')
				tilec = rgba2int(game->map->floor->r, game->map->floor->g, game->map->floor->b, 255);
			else
				tilec = rgba2int(200, 200, 200, 255);
			draw_rect_mipmap(game, (t_vec){tilex, tiley}, \
							(t_vec){MINIMAP_SIZE / 7, MINIMAP_SIZE / 7}, tilec);
			x++;
			tilex += MINIMAP_SIZE / 7;
		}
		tiley += MINIMAP_SIZE / 7; 
		y++;
	}
}
