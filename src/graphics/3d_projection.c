#include "../../inc/cub3D.h"

void	draw_walls(t_game *game, int pos_xy[2], float perp_dist, t_vec wall_pixels)
{
	int				color;
	t_ray 			*ray;
	mlx_texture_t 	*texture;
	int				x;
	int				y;

	(void)perp_dist;
	ray = &game->player->rays[pos_xy[0]];
	if (!ray->was_hit_vertical)
	{
		if (ray->ray_face_up)
		{
			texture = game->map->wall_texture->N->tex_img;
			y = (wall_pixels.x - pos_xy[1]) / (wall_pixels.x - wall_pixels.y) * texture->height;
			x = (int)(ray->wallhit_x / MAP_TILE * texture->width) % texture->width;
		}
		else
		{
			texture = game->map->wall_texture->S->tex_img;
			y = (wall_pixels.x - pos_xy[1]) / (wall_pixels.x - wall_pixels.y) * texture->height;
			x = (texture->width - 1) - (int)(ray->wallhit_x / MAP_TILE * texture->width) % texture->width;
		}
	}
	else
	{
		if (ray->ray_face_right)
		{
			texture = game->map->wall_texture->E->tex_img;
			y = (wall_pixels.x - pos_xy[1]) / (wall_pixels.x - wall_pixels.y) * texture->height;
			x = (int)(ray->wallhit_y / MAP_TILE * texture->width) % texture->width;
		}
		else
		{
			texture = game->map->wall_texture->W->tex_img;
			y = (wall_pixels.x - pos_xy[1]) / (wall_pixels.x - wall_pixels.y) * texture->height;
			x = (texture->width - 1) - (int)(ray->wallhit_y / MAP_TILE * texture->width) % texture->width;
		}
	}
	color = get_pixel(texture, x, y);
	// put_pixel(game->mlx_img, pos_xy[0], pos_xy[1], average_color(rgba2int(0,0,0,255), color, perp_dist / 1000.0)); //BONUS
	put_pixel(game->mlx_img, pos_xy[0], pos_xy[1], color);
}

void	render_3d(t_game *game)
{
	int		pos_xy[2];
	float	perp_dist;
	float	h_proj_wall;
	t_vec	wall_pos_pixel;

	pos_xy[0] = 0;
	while (pos_xy[0] < NB_RAYS)
	{
		perp_dist = game->player->rays[pos_xy[0]].distance * \
					cos(game->player->rays[pos_xy[0]].ray_angle - game->player->rot_angle);
		h_proj_wall = (MAP_TILE / perp_dist) * SCREEN_DIST;
		wall_pos_pixel.x = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
		wall_pos_pixel.y = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
		pos_xy[1] = wall_pos_pixel.x - 1;
		while (++(pos_xy[1]) < wall_pos_pixel.y)
			draw_walls(game, pos_xy, perp_dist, wall_pos_pixel);
		pos_xy[0]++;
	}
}