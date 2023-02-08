#include "cub3D.h"

void	hook(void* param)
{
	t_game	*game;
	
	game = param;
	game->current_time = mlx_get_time();
	game->frame_count++;
	move_player(game);
	cast_all_rays(game);
	draw_rect(game, (t_vec){0,0}, (t_vec){WIN_WIDTH, WIN_HEIGHT}, rgba2int(0,0,0,255));
	render_3d(game);
	// render_minimap(game);
	// render_minimap_player(game);
	// if (game->debug_render_rays == TRUE)
	// 	render_ray(game);
	// if (game->current_time - game->last_time >= 1.0)
	// {
	// 	// printf("screen_dist:%f\n", SCREEN_DIST);
	// 	if (mlx_is_key_down(game->mlx, MLX_KEY_K))
	// 		game->debug_render_rays = !game->debug_render_rays;
	// 	printf("\nFPS:%d\n", game->frame_count);
	// 	game->frame_count = 0;
	// 	game->last_time = game->current_time;
	// }

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->walk_dir->x = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->walk_dir->x = -1;
	else
		game->player->walk_dir->x = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q))
		game->player->walk_dir->y = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		game->player->walk_dir->y = 1;
	else
		game->player->walk_dir->y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->turn_dir->x = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->turn_dir->x = 1;
	else
		game->player->turn_dir->x = 0;
}

void	input_handler(t_game *game)
{
	mlx_loop_hook(game->mlx, &hook, game);
}

void	update(t_game *game)
{

	mlx_loop(game->mlx);
}

void	render(t_game *game)
{
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
}