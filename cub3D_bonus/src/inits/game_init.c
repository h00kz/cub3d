#include "../../inc/cub3D.h"

static void	error_png(char *msg, t_game *game)
{
	ft_putendl_fd(msg, 2);
	ft_free_split(game->map->map);
	ft_free2(game);
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

static void	load_n_check_texture(t_game *game)
{
	game->map->wall_texture->N->tex_img = \
				mlx_load_png(game->map->wall_texture->N->path);
	if (!game->map->wall_texture->N->tex_img)
		error_png("Error\nError on load North png texture.", game);
	game->map->wall_texture->S->tex_img = \
				mlx_load_png(game->map->wall_texture->S->path);
	if (!game->map->wall_texture->S->tex_img)
		error_png("Error\nError on load South png texture.", game);
	game->map->wall_texture->E->tex_img = \
				mlx_load_png(game->map->wall_texture->E->path);
	if (!game->map->wall_texture->E->tex_img)
		error_png("Error\nError on load East png texture.", game);
	game->map->wall_texture->W->tex_img = \
				mlx_load_png(game->map->wall_texture->W->path);
	if (!game->map->wall_texture->W->tex_img)
		error_png("Error\nError on load West png texture.", game);
}

t_game	*init_game(int ac, char **av)
{
	t_game		*game;

	game = ft_calloc(1, sizeof(t_game));
	game->map = init_map();
	game->map->map = parse(ac, av, game);
	game->map->map = ft_verif_map(game->map->map);
	// game->map->wall_texture->DOOR->path = ft_strdup("DOOR.png");
	game->map->wall_texture->DOOR->tex_img = mlx_load_png("DOOR.png");
	if (!game->map->map)
		ft_error(7, game);
	load_n_check_texture(game);
	check_player_pos(game);
	ray_interc_init(&game->ray_inter_v, &game->ray_inter_h);
	game->map->width = get_width(game->map->map);
	game->map->height = get_height(game->map->map);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d", FALSE);
	game->mlx_img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->minimap = mlx_new_image(game->mlx, MINIMAP_SIZE + 10, MINIMAP_SIZE + 10);
	game->player = init_player(game);
	game->last_time = mlx_get_time();
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	return (game);
}
