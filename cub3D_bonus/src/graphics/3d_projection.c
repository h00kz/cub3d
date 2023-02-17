/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:06 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/17 13:07:12 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	draw_walls(t_game *game, int pos_xy[2], float perp_dist, \
				t_vec wall_pixels)
{
	int				color;
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				x;
	int				y;

	if (pos_xy[1] < 0 || pos_xy[1] >= WIN_HEIGHT)
		return ;
	ray = &game->player->rays[pos_xy[0]];
	if (ray->hit_content == '3')
		return ;
	texture = get_wall_texture(game, ray);
	y = get_wall_texture_y(wall_pixels, pos_xy[1], texture);
	x = get_wall_texture_x(ray, texture);
	color = average_color(rgba2int(10, 10, 10, 255), \
				get_pixel(texture, x, y), perp_dist / 1100.0);
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
			cos(game->player->rays[pos_xy[0]].ray_angle \
				- game->player->rot_angle);
		h_proj_wall = (MAP_TILE / perp_dist) * SCREEN_DIST;
		wall_pos_pixel = get_wall_position_pixels(h_proj_wall);
		draw_vertical_strip(game, pos_xy, perp_dist, wall_pos_pixel);
		pos_xy[0]++;
	}
}

t_vec	get_wall_position_pixels(float h_proj_wall)
{
	t_vec	wall_pos_pixel;

	wall_pos_pixel.x = (WIN_HEIGHT / 2) - ((int)h_proj_wall / 2);
	wall_pos_pixel.y = (WIN_HEIGHT / 2) + ((int)h_proj_wall / 2);
	return (wall_pos_pixel);
}

void	draw_vertical_strip(t_game *game, int pos_xy[2], \
			float perp_dist, t_vec wall_pixels)
{
	pos_xy[1] = wall_pixels.x - 1;
	while (++(pos_xy[1]) < wall_pixels.y)
		draw_walls(game, pos_xy, perp_dist, wall_pixels);
}
