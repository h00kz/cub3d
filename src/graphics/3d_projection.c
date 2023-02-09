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
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	i = 0;
	color = 0;
	while (i < NB_RAYS)
	{
		perp_dist = game->player->rays[i].distance * cos(game->player->rays[i].ray_angle - game->player->rot_angle + TWO_PI);
		h_proj_wall = (MAP_TILE / perp_dist) * SCREEN_DIST;
		wall_top_pixel = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
		if (wall_bottom_pixel > WIN_HEIGHT)
			wall_bottom_pixel = WIN_HEIGHT;
		if (game->player->rays[i].ray_face_up && !game->player->rays[i].was_hit_vertical)
			color = rgba2int(255, 36, 36, 255);
		else if (game->player->rays[i].ray_face_down && !game->player->rays[i].was_hit_vertical)
			color = rgba2int(255, 242, 46, 255);
		else if (game->player->rays[i].ray_face_right && game->player->rays[i].was_hit_vertical)
			color = rgba2int(0, 155, 5, 255);
		else if (game->player->rays[i].ray_face_left && game->player->rays[i].was_hit_vertical)
			color = rgba2int(201, 0, 0, 255);
		y = -1;
		while (++y < wall_top_pixel)
			put_pixel(game->mlx_img, i, y, rgba2int(game->map->floor->r,game->map->floor->g,game->map->floor->b, 255));
		y = wall_top_pixel - 1;
		while (++y < wall_bottom_pixel)
			put_pixel(game->mlx_img, i, y , average_color(rgba2int(0,0,0,255), color, perp_dist / 1200.0));
		y = WIN_HEIGHT + 1;
		while (--y >= wall_bottom_pixel)
			put_pixel(game->mlx_img, i, y, rgba2int(game->map->cell->r,game->map->cell->g,game->map->cell->b, 255));
		i++;
	}
}