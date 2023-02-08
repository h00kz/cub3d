#include "../../inc/cub3D.h"

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
		perp_dist = game->player->rays[i].distance * cos(game->player->rays[i].ray_angle - game->player->rot_angle);
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
			put_pixel(game->mlx_img, i, y, rgba2int(112,218,255,255));
		y = wall_top_pixel - 1;
		while (++y < wall_bottom_pixel)
			put_pixel(game->mlx_img, i, y , color);
		y = WIN_HEIGHT + 1;
		while (--y > wall_bottom_pixel)
			put_pixel(game->mlx_img, i, y, rgba2int(102,51,0,255));
		i++;
	}
}