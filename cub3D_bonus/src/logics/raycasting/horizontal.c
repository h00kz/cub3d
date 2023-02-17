/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:35 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/17 11:26:30 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_at_map(t_game *game, float x, float y)
{
	int	x_index;
	int	y_index;

	x_index = floor(x / MAP_TILE);
	y_index = floor(y / MAP_TILE);
	return (game->map->map[y_index][x_index]);
}

void	horizontal_wall_hits(t_game *game)
{
	while (is_in_map(game, *(game->ray_inter_h.next_touch)))
	{
		if (game->interct.is_ray_fac_up)
			game->ray_inter_h.to_check->y = game->ray_inter_h.next_touch->y - 1;
		else
			game->ray_inter_h.to_check->y = game->ray_inter_h.next_touch->y;
		game->ray_inter_h.to_check->x = game->ray_inter_h.next_touch->x;
		if (!get_collision(game, *(game->ray_inter_h.to_check)))
		{
			game->ray_inter_h.wall_hit_x = game->ray_inter_h.next_touch->x;
			game->ray_inter_h.wall_hit_y = game->ray_inter_h.next_touch->y;
			game->ray_inter_h.wall_content = \
				get_at_map(game, game->ray_inter_h.to_check->x, \
					game->ray_inter_h.to_check->y);
			game->ray_inter_h.found_wall_hit = TRUE;
			break ;
		}
		game->ray_inter_h.next_touch->x += game->ray_inter_h.step->x;
		game->ray_inter_h.next_touch->y += game->ray_inter_h.step->y;
	}
}

void	horizontal_interc(t_game *game, float ray_angle)
{
	reset_ray(&game->ray_inter_h);
	game->ray_inter_h.interc->y = floor(game->player->position->y / \
		(MAP_TILE)) * (MAP_TILE);
	if (game->interct.is_ray_fac_down)
		game->ray_inter_h.interc->y += MAP_TILE;
	game->ray_inter_h.interc->x = game->player->position->x + \
		(game->ray_inter_h.interc->y - game->player->position->y) \
										/ tan(ray_angle);
	game->ray_inter_h.step->y = MAP_TILE;
	if (game->interct.is_ray_fac_up)
		game->ray_inter_h.step->y *= -1;
	game->ray_inter_h.step->x = (MAP_TILE) \
								/ tan(ray_angle);
	if ((game->interct.is_ray_fac_left && game->ray_inter_h.step->x > 0) || \
		(game->interct.is_ray_fac_right && game->ray_inter_h.step->x < 0))
		game->ray_inter_h.step->x *= -1;
	game->ray_inter_h.next_touch->x = game->ray_inter_h.interc->x;
	game->ray_inter_h.next_touch->y = game->ray_inter_h.interc->y;
	horizontal_wall_hits(game);
}
