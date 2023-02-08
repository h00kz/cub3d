#include "../../inc/cub3D.h"

void	draw_rect(t_game *game, t_vec pos, t_vec size, int color)
{
	int	y;
	int	x;

	y = pos.y;
	while (y <= pos.y + size.y)
	{
		x = pos.x;
		while (x <= pos.x + size.x)
		{
			put_pixel(game->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}