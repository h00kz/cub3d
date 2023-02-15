#include "../../inc/cub3D.h"

static void	error_png(char *msg, t_wall *wall)
{
	ft_putendl_fd(msg, 2);
	free(wall->N->path);
	free(wall->S->path);
	free(wall->E->path);
	free(wall->W->path);
	free(wall->N);
	free(wall->S);
	free(wall->E);
	free(wall->W);
	free(wall);
	exit(1);
}

static void	ray_interc_init(t_interc *v, t_interc *h)
{
	v->interc = ft_calloc(1, sizeof(t_vec));
	v->next_touch = ft_calloc(1, sizeof(t_vec));
	v->to_check = ft_calloc(1, sizeof(t_vec));
	v->step = ft_calloc(1, sizeof(t_vec));
	h->interc = ft_calloc(1, sizeof(t_vec));
	h->next_touch = ft_calloc(1, sizeof(t_vec));
	h->to_check = ft_calloc(1, sizeof(t_vec));
	h->step = ft_calloc(1, sizeof(t_vec));
}

static void	load_n_check_texture(t_wall *wall)
{
	wall->N->tex_img = mlx_load_png(wall->N->path);
	if (!wall->N->tex_img)
		error_png("Error\nError on load North png texture.", wall);
	wall->S->tex_img = mlx_load_png(wall->S->path);
	if (!wall->S->tex_img)
		error_png("Error\nError on load South png texture.", wall);
	wall->E->tex_img = mlx_load_png(wall->E->path);
	if (!wall->E->tex_img)
		error_png("Error\nError on load East png texture.", wall);
	wall->W->tex_img = mlx_load_png(wall->W->path);
	if (!wall->W->tex_img)
		error_png("Error\nError on load West png texture.", wall);
}

t_game	*init_game(int ac, char **av)
{
	t_game		*game;

	game = ft_calloc(1, sizeof(t_game));
	ray_interc_init(&game->ray_inter_v, &game->ray_inter_h);
	game->map = init_map();
	game->map->map = parse(ac, av, game);
	game->map->map = ft_verif_map(game->map->map);
	load_n_check_texture(game->map->wall_texture);
	check_player_pos(game);
	game->map->width = get_width(game->map->map);
	game->map->height = get_height(game->map->map);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d", FALSE);
	game->mlx_img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->player = init_player(game);
	game->last_time = mlx_get_time();
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->frame_count = 0;
	game->debug_render_rays = FALSE;
	return (game);
}
