#include "../../inc/cub3D.h"

t_game	*init_game(int ac, char **av)
{
	t_game		*game;

	game = ft_calloc(1, sizeof(t_game));
	game->ray_inter_v.interc = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_v.next_touch = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_v.to_check = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_v.step = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_h.interc = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_h.next_touch = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_h.to_check = ft_calloc(1, sizeof(t_vec));
	game->ray_inter_h.step = ft_calloc(1, sizeof(t_vec));
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d", FALSE);
	game->mlx_img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->map = init_map();
	game->map->map = parse(ac, av, game);
	game->map->map = ft_verif_map(game->map->map);
	check_player_pos(game);
	game->map->width = get_width(game->map->map);
	game->map->height = get_height(game->map->map);
	game->player = init_player(game);
	game->last_time = mlx_get_time();
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->frame_count = 0;
	game->debug_render_rays = FALSE;
	return (game);
}