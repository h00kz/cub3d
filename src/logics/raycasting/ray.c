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

static void	reset_ray(t_interc *hv)
{
	hv->found_wall_hit = FALSE;
	hv->wall_hit_x = 0.0;
	hv->wall_hit_y = 0.0;
	hv->next_touch->x = 0.0;
	hv->next_touch->y = 0.0;
	hv->wall_content = 0.0;
	hv->hit_distance = 0.0;
}

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
			game->ray_inter_v.found_wall_hit = TRUE;
			break;
		}
		game->ray_inter_v.next_touch->x += game->ray_inter_v.step->x;
		game->ray_inter_v.next_touch->y += game->ray_inter_v.step->y;
	}
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
			game->ray_inter_h.found_wall_hit = TRUE;
			break;
		}
		game->ray_inter_h.next_touch->x += game->ray_inter_h.step->x;
		game->ray_inter_h.next_touch->y += game->ray_inter_h.step->y;
	}
}

void	vertical_interc(t_game *game, float ray_angle)
{
	reset_ray(&game->ray_inter_v);
	game->ray_inter_v.interc->x = floor(game->player->position->x / (MAP_TILE)) * (MAP_TILE);
	if (game->interct.is_ray_fac_right)
		game->ray_inter_v.interc->x += (MAP_TILE);
	game->ray_inter_v.interc->y = game->player->position->y + \
		(game->ray_inter_v.interc->x - game->player->position->x) * tan(ray_angle);
	game->ray_inter_v.step->x = (MAP_TILE);
	if (game->interct.is_ray_fac_left)
		game->ray_inter_v.step->x *= -1;
	game->ray_inter_v.step->y = (MAP_TILE) * tan(ray_angle);
	if ((game->interct.is_ray_fac_up && game->ray_inter_v.step->y > 0) ||
		(game->interct.is_ray_fac_down && game->ray_inter_v.step->y < 0))
		game->ray_inter_v.step->y *= -1;
	game->ray_inter_v.next_touch->x = game->ray_inter_v.interc->x;
	game->ray_inter_v.next_touch->y = game->ray_inter_v.interc->y;
	vertical_wall_hits(game);
}

void	horizontal_interc(t_game *game, float ray_angle)
{
	reset_ray(&game->ray_inter_h);
	game->ray_inter_h.interc->y = floor(game->player->position->y / (MAP_TILE)) * (MAP_TILE);
	if (game->interct.is_ray_fac_down)
		game->ray_inter_h.interc->y += MAP_TILE;
	game->ray_inter_h.interc->x = game->player->position->x + \
		(game->ray_inter_h.interc->y - game->player->position->y) / tan(ray_angle);
	game->ray_inter_h.step->y = MAP_TILE;
	if (game->interct.is_ray_fac_up)
		game->ray_inter_h.step->y *= -1;
	game->ray_inter_h.step->x = (MAP_TILE) / tan(ray_angle);
	if ((game->interct.is_ray_fac_left && game->ray_inter_h.step->x > 0) ||
		(game->interct.is_ray_fac_right && game->ray_inter_h.step->x < 0))
		game->ray_inter_h.step->x *= -1;
	game->ray_inter_h.next_touch->x = game->ray_inter_h.interc->x;
	game->ray_inter_h.next_touch->y = game->ray_inter_h.interc->y;
	horizontal_wall_hits(game);
}

static void	put_on_rays_struct(t_interc hv, t_game *game, int was_hit_v, int ray_id)
{
	game->player->rays[ray_id].distance = hv.hit_distance;
	game->player->rays[ray_id].wallhit_x = hv.wall_hit_x;
	game->player->rays[ray_id].wallhit_y = hv.wall_hit_y;
	game->player->rays[ray_id].hit_content = hv.wall_content;
	game->player->rays[ray_id].was_hit_vertical = was_hit_v;
}

static void	take_smallest_r_infos(t_game *game, float ray_angle, int ray_id)
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

void	cast_ray(t_game *game, float ray_angle, int ray_id)
{
	game->interct.is_ray_fac_down = (ray_angle > 0 && ray_angle < PI);
	game->interct.is_ray_fac_up = !game->interct.is_ray_fac_down;
	game->interct.is_ray_fac_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	game->interct.is_ray_fac_left = !game->interct.is_ray_fac_right;
	horizontal_interc(game, ray_angle);
	vertical_interc(game, ray_angle);
	take_smallest_r_infos(game, ray_angle, ray_id);
}

void	render_ray(t_game *game)
{
	t_vec	end_line;
	int		i;

	i = 0;
	while (i < NB_RAYS)
	{
		end_line.x = game->player->rays[i].wallhit_x;
		end_line.y = game->player->rays[i].wallhit_y;
		draw_line(game, game->player->position, &end_line, rgba2int(220, 10, 10, 128));
		i++;
	}
}

float	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
	return (*angle);
}

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