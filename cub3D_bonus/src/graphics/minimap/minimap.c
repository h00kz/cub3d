#include "cub3D.h"

void	render_minimap_player(t_game *game)
{
	t_vec	end_line;
	t_vec	pos_offset;
	t_vec	start;

	start = (t_vec){game->minimap->width / 2 - 8, \
					game->minimap->height / 2 - 8};
	pos_offset = start;
	pos_offset.x -= 10 / 2;
	pos_offset.y -= 10 / 2;
	end_line.x = (game->minimap->width / 2 - 5) + cos(game->player->rot_angle) * 40;
	end_line.y = (game->minimap->height / 2 - 5) + sin(game->player->rot_angle) * 40;
	draw_rect_mipmap(game, pos_offset, (t_vec){12, 12}, rgba2int(120, 230, 12, 255));
	draw_line_mipmap(game, &start, &end_line, rgba2int(200, 90, 90, 255));
}
