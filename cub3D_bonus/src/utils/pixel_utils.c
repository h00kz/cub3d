/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:34:31 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 11:35:37 by jlarrieu         ###   ########.fr       */
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
