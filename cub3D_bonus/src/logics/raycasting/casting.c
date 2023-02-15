/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:29 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 11:38:20 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	int		ray_id;

	ray_id = 0;
	ray_angle = game->player->rot_angle - HALF_FOV;
	while (ray_id < NB_RAYS)
	{
		normalize_angle(&ray_angle);
		cast_ray(game, ray_angle, ray_id);
		ray_angle += DELTA_ANGLE;
		ray_id++;
	}
}

void	cast_ray(t_game *game, float ray_angle, int ray_id)
{
	game->interct.is_ray_fac_down = (ray_angle > 0 && ray_angle < PI);
	game->interct.is_ray_fac_up = !game->interct.is_ray_fac_down;
	game->interct.is_ray_fac_right = (ray_angle < 0.5 * PI || \
									ray_angle > 1.5 * PI);
	game->interct.is_ray_fac_left = !game->interct.is_ray_fac_right;
	horizontal_interc(game, ray_angle);
	vertical_interc(game, ray_angle);
	take_smallest_r_infos(game, ray_angle, ray_id);
}

float	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
	return (*angle);
}
