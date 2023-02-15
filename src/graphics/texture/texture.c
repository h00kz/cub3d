/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:32:01 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 11:32:02 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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