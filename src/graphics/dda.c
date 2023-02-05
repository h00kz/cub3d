#include "../../inc/cub3D.h"

void	draw_line(t_game *game, t_vec *start, t_vec *end, int color)
{
	t_vec	delta;
	t_vec	pos_inc;
	t_vec	current_pos;
	float	longest_side_len;
	int		i;

	i = 0;
	delta.x = (end->x - start->x);
	delta.y = (end->y - start->y);
	longest_side_len = fmax(fabs(delta.x),fabs(delta.y));
	pos_inc.x = delta.x / longest_side_len;
	pos_inc.y = delta.y / longest_side_len;
	current_pos.x = start->x;
	current_pos.y = start->y;
	while (i < longest_side_len)
	{
		put_pixel(game->mlx_img, current_pos.x, current_pos.y, color);
		current_pos.x += pos_inc.x;
		current_pos.y += pos_inc.y;
		i++;
	}
}