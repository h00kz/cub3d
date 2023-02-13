#include "../../inc/cub3D.h"

void	draw_walls(t_game *game, int pos_xy[2], float perp_dist, t_vec wall_pos_pixel_bis)
{
	int	color;

	if (game->player->rays[pos_xy[0]].ray_face_up && \
			!game->player->rays[pos_xy[0]].was_hit_vertical) // NORD
		color = get_pixel(game->map->wall_texture->N->tex_img, \
				(int)game->player->rays[pos_xy[0]].wallhit_x % MAP_TILE, \
				(wall_pos_pixel_bis.x - pos_xy[1]) / (wall_pos_pixel_bis.x - wall_pos_pixel_bis.y) * MAP_TILE);
	else if (game->player->rays[pos_xy[0]].ray_face_down && \
			!game->player->rays[pos_xy[0]].was_hit_vertical) // SUD
		color = get_pixel(game->map->wall_texture->S->tex_img, \
				(MAP_TILE - 1) - (int)game->player->rays[pos_xy[0]].wallhit_x % MAP_TILE, \
				(wall_pos_pixel_bis.x - pos_xy[1]) / (wall_pos_pixel_bis.x - wall_pos_pixel_bis.y) * MAP_TILE);
	else if (game->player->rays[pos_xy[0]].ray_face_right && \
			game->player->rays[pos_xy[0]].was_hit_vertical) // EST
		color = get_pixel(game->map->wall_texture->E->tex_img, \
				(int)game->player->rays[pos_xy[0]].wallhit_y % MAP_TILE, \
				(wall_pos_pixel_bis.x - pos_xy[1]) / (wall_pos_pixel_bis.x - wall_pos_pixel_bis.y) * MAP_TILE);
	else if (game->player->rays[pos_xy[0]].ray_face_left && \
			game->player->rays[pos_xy[0]].was_hit_vertical) // OUEST
		color = get_pixel(game->map->wall_texture->W->tex_img, \
				(MAP_TILE - 1) - (int)game->player->rays[pos_xy[0]].wallhit_y % MAP_TILE, \
				(wall_pos_pixel_bis.x - pos_xy[1]) / (wall_pos_pixel_bis.x - wall_pos_pixel_bis.y) * MAP_TILE);
	put_pixel(game->mlx_img, pos_xy[0], pos_xy[1], average_color(rgba2int(0,0,0,255), color, perp_dist / 1000.0));
}

void	render_3d(t_game *game)
{
	int		pos_xy[2];
	float	perp_dist;
	float	h_proj_wall;
	t_vec	wall_pos_pixel;
	t_vec	wall_pos_pixel_bis;

	pos_xy[0] = 0;
	while (pos_xy[0] < NB_RAYS)
	{
		perp_dist = game->player->rays[pos_xy[0]].distance * \
					cos(game->player->rays[pos_xy[0]].ray_angle - game->player->rot_angle);
		h_proj_wall = (MAP_TILE / perp_dist) * SCREEN_DIST;
		wall_pos_pixel.x = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
		wall_pos_pixel_bis.x = wall_pos_pixel.x;
		if (wall_pos_pixel.x < 0)
			wall_pos_pixel.x = 0;
		wall_pos_pixel.y = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
		wall_pos_pixel_bis.y = wall_pos_pixel.y;
		if (wall_pos_pixel.y > WIN_HEIGHT)
			wall_pos_pixel.y = WIN_HEIGHT;
		pos_xy[1] = wall_pos_pixel.x - 1;
		while (++(pos_xy[1]) < wall_pos_pixel.y)
			draw_walls(game, pos_xy, perp_dist, wall_pos_pixel_bis);
		pos_xy[0]++;
	}
}