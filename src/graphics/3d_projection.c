#include "../../inc/cub3D.h"

void draw_walls(t_game *game, int pos_xy[2], t_vec wall_pixels)
{
	int				color;
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				x;
	int				y;

	if (pos_xy[1] <= 0 || pos_xy[1] >= WIN_HEIGHT)
		return ;
	ray = &game->player->rays[pos_xy[0]];
	texture = get_wall_texture(game, ray);
	y = get_wall_texture_y(wall_pixels, pos_xy[1], texture);
	x = get_wall_texture_x(ray, texture);
	color = get_pixel(texture, x, y);
	put_pixel(game->mlx_img, pos_xy[0], pos_xy[1], color);
}

void render_3d(t_game *game)
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
		wall_pos_pixel = get_wall_position_pixels(h_proj_wall);
		draw_vertical_strip(game, pos_xy, wall_pos_pixel);
		pos_xy[0]++;
	}

}

mlx_texture_t *get_wall_texture(t_game *game, t_ray *ray)
{
	if (!ray->was_hit_vertical)
	{
		if (ray->ray_face_up)
			return (game->map->wall_texture->N->tex_img);
		else
			return (game->map->wall_texture->S->tex_img);
	}
	else
	{
		if (ray->ray_face_right)
			return (game->map->wall_texture->E->tex_img);
		else
			return (game->map->wall_texture->W->tex_img);
	}
}

int get_wall_texture_y(t_vec wall_pixels, int pos_y, mlx_texture_t *texture)
{
	return ((wall_pixels.x - pos_y) / (wall_pixels.x - wall_pixels.y) * texture->height);
}

int get_wall_texture_x(t_ray *ray, mlx_texture_t *texture)
{
	if (!ray->was_hit_vertical)
	{
		if (ray->ray_face_up)
			return ((int)(ray->wallhit_x / MAP_TILE * texture->width) % texture->width);
		else
			return ((texture->width - 1) - \
					(int)(ray->wallhit_x / MAP_TILE * texture->width) % texture->width);
	}
	else
	{
		if (ray->ray_face_right)
			return ((int)(ray->wallhit_y / MAP_TILE * texture->width) % texture->width);
		else
			return ((texture->width - 1) - \
					(int)(ray->wallhit_y / MAP_TILE * texture->width) % texture->width);
	}
}

t_vec get_wall_position_pixels(float h_proj_wall)
{
	t_vec	wall_pos_pixel;

	wall_pos_pixel.x = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
	wall_pos_pixel.y = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
	return (wall_pos_pixel);

}

void draw_vertical_strip(t_game *game, int pos_xy[2], t_vec wall_pixels)
{
	pos_xy[1] = wall_pixels.x - 1;
	while (++(pos_xy[1]) < wall_pixels.y)
		draw_walls(game, pos_xy, wall_pixels);
}