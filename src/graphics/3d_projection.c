#include "../../inc/cub3D.h"


int	average_color(int start_color, int end_color, float f)
{
	int	new_color;
	int tmp;
	int i;

	i = 0;
	if (f < 0 || f > 1)
		return (start_color);
	new_color = 0;
	while (i < 4)
	{
		tmp = ((start_color >> (8 * i)) & 0xff) * f + ((end_color >> (8 * i)) & 0xff) * (1.0 - f);
		if (tmp > 255)
			tmp = 0;
		new_color += tmp << (i * 8);
		i++;
	}
	return (new_color);
}

void	render_3d(t_game *game)
{
	int		i;
	int		y;
	int		color;
	float	perp_dist;
	float	h_proj_wall;
	float	wall_top_pixel;
	float	wall_bottom_pixel;
	float	wall_top_pixel_bis;
	float	wall_bottom_pixel_bis;

	i = 0;
	color = 0;
	while (i < NB_RAYS)
	{
		perp_dist = game->player->rays[i].distance * cos(game->player->rays[i].ray_angle - game->player->rot_angle + TWO_PI);
		h_proj_wall = (MAP_TILE / perp_dist) * SCREEN_DIST;
		wall_top_pixel = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
		wall_top_pixel_bis = wall_top_pixel;
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
		wall_bottom_pixel_bis = wall_bottom_pixel;
		if (wall_bottom_pixel > WIN_HEIGHT)
			wall_bottom_pixel = WIN_HEIGHT;
		// y = -1;
		// while (++y <= wall_top_pixel)
		// 	put_pixel(game->mlx_img, i, y, rgba2int(game->map->cell->r,game->map->cell->g,game->map->cell->b, 255));
		y = wall_top_pixel - 1;
		while (++y < wall_bottom_pixel)
		{
			if (game->player->rays[i].ray_face_up && !game->player->rays[i].was_hit_vertical) // NORD
				color = get_pixel(game->map->wall_texture->N->tex_img, (((int)game->player->rays[i].wallhit_x % MAP_TILE)), \
						(wall_top_pixel_bis - y) / (wall_top_pixel_bis - wall_bottom_pixel_bis) * MAP_TILE);
			else if (game->player->rays[i].ray_face_down && !game->player->rays[i].was_hit_vertical) // SUD
				color = get_pixel(game->map->wall_texture->S->tex_img, ((MAP_TILE - 1) - ((int)(game->player->rays[i].wallhit_x) % MAP_TILE)), \
						(wall_top_pixel_bis - y) / (wall_top_pixel_bis - wall_bottom_pixel_bis) * MAP_TILE);
			else if (game->player->rays[i].ray_face_right && game->player->rays[i].was_hit_vertical) // EST
				color = get_pixel(game->map->wall_texture->E->tex_img, (((int)(game->player->rays[i].wallhit_y) % MAP_TILE)), \
						(wall_top_pixel_bis - y) / (wall_top_pixel_bis - wall_bottom_pixel_bis) * MAP_TILE);
			else if (game->player->rays[i].ray_face_left && game->player->rays[i].was_hit_vertical) // OUEST
				color = get_pixel(game->map->wall_texture->W->tex_img, ((MAP_TILE - 1) - (int)game->player->rays[i].wallhit_y % MAP_TILE), \
						(wall_top_pixel_bis - y) / (wall_top_pixel_bis - wall_bottom_pixel_bis) * MAP_TILE);
			put_pixel(game->mlx_img, i, y, average_color(rgba2int(0,0,0,255), color, perp_dist / 1200.0));
		}
		// y = WIN_HEIGHT + 1;
		// while (--y >= wall_bottom_pixel)
		// 	put_pixel(game->mlx_img, i, y, rgba2int(game->map->floor->r,game->map->floor->g,game->map->floor->b, 255));
		// put_pixel(game->mlx_img, i, y, average_color(rgba2int(game->map->floor->r,game->map->floor->g,game->map->floor->b, 255), color, y / (wall_bottom_pixel + 50.0)));
		i++;
	}
}