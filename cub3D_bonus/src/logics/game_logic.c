/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:39:54 by jlarrieu          #+#    #+#             */
/*   Updated: 2023/02/16 18:23:41 by jlarrieu         ###   ########.fr       */
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

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_game *game;
	
	game = param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		if (game->player->fire == FALSE)
			game->player->fire = TRUE;
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
	static int	i_frame = 0;

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
	if (game->player->fire)
	{
		if (!(frame % 2))
		{
			mlx_draw_texture(game->weapon, game->player->weapon[i_frame].tex_img, 0, 0);
			i_frame++;
		}
		if (i_frame == 4)
		{
			i_frame = 0;
			mlx_draw_texture(game->weapon, game->player->weapon[i_frame].tex_img, 0, 0);
			game->player->fire = false;
		}
	}
	frame++;
	if (game->current_time - game->last_time >= 1.0)
	{
		printf("FPS:%d\n", frame);
		frame = 0;
		game->last_time = game->current_time;
	}
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = param;
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_RELEASE)
	{
		if (game->map->map[((int)(game->player->position->y) / MAP_TILE) + 1][((int)(game->player->position->x) / MAP_TILE)] == '2')
			game->map->map[((int)(game->player->position->y) / MAP_TILE) + 1][((int)(game->player->position->x) / MAP_TILE)] = '3';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE) - 1][((int)(game->player->position->x) / MAP_TILE)] == '2')
			game->map->map[((int)(game->player->position->y) / MAP_TILE) - 1][((int)(game->player->position->x) / MAP_TILE)] = '3';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) + 1] == '2')
			game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) + 1] = '3';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) - 1] == '2')
			game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) - 1] = '3';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE) + 1][((int)(game->player->position->x) / MAP_TILE)] == '3')
			game->map->map[((int)(game->player->position->y) / MAP_TILE) + 1][((int)(game->player->position->x) / MAP_TILE)] = '2';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE) - 1][((int)(game->player->position->x) / MAP_TILE)] == '3')
			game->map->map[((int)(game->player->position->y) / MAP_TILE) - 1][((int)(game->player->position->x) / MAP_TILE)] = '2';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) + 1] == '3')
			game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) + 1] = '2';
		else if (game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) - 1] == '3')
			game->map->map[((int)(game->player->position->y) / MAP_TILE)][((int)(game->player->position->x) / MAP_TILE) - 1] = '2';
	}
}