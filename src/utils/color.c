#include "../../inc/cub3D.h"

int	rgba2int(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

float	distance_ab(t_vec a, t_vec b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && x <= WIN_WIDTH && y > 0 && y <= WIN_HEIGHT)
	{
		uint8_t* pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
		draw_pixel(pixelstart, color);
	}
}