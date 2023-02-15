/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:41 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 11:36:37 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3D.h"

t_ray	*init_rays(int nb_rays)
{
	t_ray	*rays;

	rays = ft_calloc(nb_rays, sizeof(t_ray));
	rays->ray_angle = 0;
	rays->wallhit_x = 0;
	rays->wallhit_y = 0;
	rays->distance = 0;
	rays->was_hit_vertical = 0;
	rays->hit_content = 0;
	rays->ray_face_up = 0;
	rays->ray_face_down = 0;
	rays->ray_face_left = 0;
	rays->ray_face_right = 0;
	return (rays);
}

void	reset_ray(t_interc *hv)
{
	hv->found_wall_hit = FALSE;
	hv->wall_hit_x = 0.0;
	hv->wall_hit_y = 0.0;
	hv->next_touch->x = 0.0;
	hv->next_touch->y = 0.0;
	hv->wall_content = 0.0;
	hv->hit_distance = 0.0;
}

void	put_on_rays_struct(t_interc hv, t_game *game, int was_hit_v, int ray_id)
{
	game->player->rays[ray_id].distance = hv.hit_distance;
	game->player->rays[ray_id].wallhit_x = hv.wall_hit_x;
	game->player->rays[ray_id].wallhit_y = hv.wall_hit_y;
	game->player->rays[ray_id].hit_content = hv.wall_content;
	game->player->rays[ray_id].was_hit_vertical = was_hit_v;
}

void	take_smallest_r_infos(t_game *game, float ray_angle, int ray_id)
{
	if (game->ray_inter_h.found_wall_hit)
		game->ray_inter_h.hit_distance = distance_ab(*(game->player->position), \
		(t_vec){game->ray_inter_h.wall_hit_x, game->ray_inter_h.wall_hit_y});
	else
		game->ray_inter_h.hit_distance = FLT_MAX;
	if (game->ray_inter_v.found_wall_hit)
		game->ray_inter_v.hit_distance = distance_ab(*(game->player->position), \
		(t_vec){game->ray_inter_v.wall_hit_x, game->ray_inter_v.wall_hit_y});
	else
		game->ray_inter_v.hit_distance = FLT_MAX;
	if (game->ray_inter_v.hit_distance < game->ray_inter_h.hit_distance)
		put_on_rays_struct(game->ray_inter_v, game, TRUE, ray_id);
	else
		put_on_rays_struct(game->ray_inter_h, game, FALSE, ray_id);
	game->player->rays[ray_id].ray_angle = ray_angle;
	game->player->rays[ray_id].ray_face_down = game->interct.is_ray_fac_down;
	game->player->rays[ray_id].ray_face_up = game->interct.is_ray_fac_up;
	game->player->rays[ray_id].ray_face_left = game->interct.is_ray_fac_left;
	game->player->rays[ray_id].ray_face_right = game->interct.is_ray_fac_right;
}
