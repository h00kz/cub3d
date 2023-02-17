/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:34:31 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/17 12:14:55 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color & 0xff);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 24);
}

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		pixelstart = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
		draw_pixel(pixelstart, color);
	}
}

uint32_t	get_pixel(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	return (((uint32_t *)texture->pixels)[(y * texture->width + x)]);
}

void	check_door(t_game *game, int player_y_tile, int player_x_tile)
{
	if (game->map->map[player_y_tile + 1][player_x_tile] == '2')
		game->map->map[player_y_tile + 1][player_x_tile] = '3';
	else if (game->map->map[player_y_tile - 1][player_x_tile] == '2')
		game->map->map[player_y_tile - 1][player_x_tile] = '3';
	else if (game->map->map[player_y_tile][player_x_tile + 1] == '2')
		game->map->map[player_y_tile][player_x_tile + 1] = '3';
	else if (game->map->map[player_y_tile][player_x_tile - 1] == '2')
		game->map->map[player_y_tile][player_x_tile - 1] = '3';
	else if (game->map->map[player_y_tile + 1][player_x_tile] == '3')
		game->map->map[player_y_tile + 1][player_x_tile] = '2';
	else if (game->map->map[player_y_tile - 1][player_x_tile] == '3')
		game->map->map[player_y_tile - 1][player_x_tile] = '2';
	else if (game->map->map[player_y_tile][player_x_tile + 1] == '3')
		game->map->map[player_y_tile][player_x_tile + 1] = '2';
	else if (game->map->map[player_y_tile][player_x_tile - 1] == '3')
		game->map->map[player_y_tile][player_x_tile - 1] = '2';
}
