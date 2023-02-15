/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:39:54 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/15 20:48:41 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_routine(void *param)
{
	t_game	*game;

	game = param;
	input_handler(game);
	render(game);
}

void	input_handler(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->walk_dir->x = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->walk_dir->x = -1;
	else
		game->player->walk_dir->x = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->walk_dir->y = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->walk_dir->y = 1;
	else
		game->player->walk_dir->y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q))
		game->player->turn_dir->x = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		game->player->turn_dir->x = 1;
	else
		game->player->turn_dir->x = 0;
}

void	render(t_game *game)
{
	static int	frame = 0;

	move_player(game);
	cast_all_rays(game);
	draw_rect(game, (t_vec){0, 0}, (t_vec){WIN_WIDTH, WIN_HEIGHT / 2}, \
	rgba2int(game->map->cell->r, game->map->cell->g, game->map->cell->b, 255));
	draw_rect(game, (t_vec){0, WIN_HEIGHT / 2}, \
			(t_vec){WIN_WIDTH, WIN_HEIGHT}, \
			rgba2int(game->map->floor->r, game->map->floor->g, \
			game->map->floor->b, 255));
	render_3d(game);
	draw_rect(game, (t_vec){0, 0}, (t_vec){MINIMAP_SIZE + 20, MINIMAP_SIZE + 20}, rgba2int(40,40,40,255));
	render_minimap(game);
	render_minimap_player(game);
	game->current_time = mlx_get_time();
	frame++;
	if (game->current_time - game->last_time >= 1.0)
	{
		printf("FPS:%d\n", frame);
		frame = 0;
		game->last_time = game->current_time;
	}
}
