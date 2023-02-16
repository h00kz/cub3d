/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:46 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/16 14:33:47 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	vertical_wall_hits(t_game *game)
{
	while (is_in_map(game, *(game->ray_inter_v.next_touch)))
	{
		if (game->interct.is_ray_fac_left)
			game->ray_inter_v.to_check->x = game->ray_inter_v.next_touch->x - 1;
		else
			game->ray_inter_v.to_check->x = game->ray_inter_v.next_touch->x;
		game->ray_inter_v.to_check->y = game->ray_inter_v.next_touch->y;
		if (!get_collision(game, *(game->ray_inter_v.to_check)))
		{
			game->ray_inter_v.wall_hit_x = game->ray_inter_v.next_touch->x;
			game->ray_inter_v.wall_hit_y = game->ray_inter_v.next_touch->y;
			game->ray_inter_v.wall_content = get_at_map(game, game->ray_inter_v.to_check->x, game->ray_inter_v.to_check->y);
			game->ray_inter_v.found_wall_hit = TRUE;
			break ;
		}
		game->ray_inter_v.next_touch->x += game->ray_inter_v.step->x;
		game->ray_inter_v.next_touch->y += game->ray_inter_v.step->y;
	}
}

void	vertical_interc(t_game *game, float ray_angle)
{
	reset_ray(&game->ray_inter_v);
	game->ray_inter_v.interc->x = floor(game->player->position->x \
	/ (MAP_TILE)) * (MAP_TILE);
	if (game->interct.is_ray_fac_right)
		game->ray_inter_v.interc->x += (MAP_TILE);
	game->ray_inter_v.interc->y = game->player->position->y + \
	(game->ray_inter_v.interc->x - game->player->position->x) * tan(ray_angle);
	game->ray_inter_v.step->x = (MAP_TILE);
	if (game->interct.is_ray_fac_left)
		game->ray_inter_v.step->x *= -1;
	game->ray_inter_v.step->y = (MAP_TILE) \
								* tan(ray_angle);
	if ((game->interct.is_ray_fac_up && game->ray_inter_v.step->y > 0) || \
		(game->interct.is_ray_fac_down && game->ray_inter_v.step->y < 0))
		game->ray_inter_v.step->y *= -1;
	game->ray_inter_v.next_touch->x = game->ray_inter_v.interc->x;
	game->ray_inter_v.next_touch->y = game->ray_inter_v.interc->y;
	vertical_wall_hits(game);
}
