#include "cub3D.h"

static void draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		uint8_t* pixelstart = &image->pixels[(y * image->width + x) * sizeof(uint32_t)];
		draw_pixel(pixelstart, color);
	}
}

uint32_t	get_pixel(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	return (((uint32_t *)texture->pixels)[(y * texture->width + x)]);
}