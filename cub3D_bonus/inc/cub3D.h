#ifndef CUB3D_HPP
# define CUB3D_HPP

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// ----------------------- DEFINES ------------------------- //
# define TRUE 1
# define FALSE 0
# define PI 3.14159265
# define TWO_PI 6.28318530
# define WIN_WIDTH 1600
# define WIN_HALF_W (WIN_WIDTH / 2)
# define WIN_HEIGHT 900
# define WIN_HALF_H (WIN_HEIGHT / 2)
# define MAP_TILE 64
# define MINIMAP_SIZE 200
# define FOV_ANGLE (60 * (PI / 180.0))
# define HALF_FOV (FOV_ANGLE / 2)
# define NB_RAYS WIN_WIDTH
# define DELTA_ANGLE (FOV_ANGLE / NB_RAYS)
# define SCREEN_DIST (WIN_HALF_W / tan(HALF_FOV))

// ----------------------- STRUCTS ------------------------- //
typedef struct s_game t_game;
typedef struct s_ray t_ray;
typedef struct s_interc t_interc;
typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_vec t_vec;
typedef struct s_rect t_rect;
typedef struct s_texture t_texture;
typedef struct s_wall t_wall;
typedef struct s_color t_color;

typedef struct s_texture
{
	mlx_texture_t	*tex_img;
	char			*path;
}	t_texture;

typedef struct s_wall
{
	t_texture	*N;
	t_texture	*S;
	t_texture	*E;
	t_texture	*W;
	t_texture	*DOOR;
}	t_wall;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_rect
{
	t_vec	position;
	t_vec	size;
	t_color color;
}	t_rect;

typedef struct s_ray
{
	float		ray_angle;
	float		wallhit_x;
	float		wallhit_y;
	float		distance;
	int			was_hit_vertical;
	int			hit_content;
	int			ray_face_up;
	int			ray_face_down;
	int			ray_face_left;
	int			ray_face_right;
}	t_ray;

typedef struct s_interc
{
	int			found_wall_hit;
	int			wall_content;
	int			is_ray_fac_down;
	int			is_ray_fac_up;
	int			is_ray_fac_right;
	int			is_ray_fac_left;
	float		hit_distance;
	float		wall_hit_x;
	float		wall_hit_y;
	t_vec		*next_touch;
	t_vec		*to_check;
	t_vec		*interc;
	t_vec		*step;
}	t_interc;

typedef struct s_map
{
	t_wall		*wall_texture;
	t_color		*floor;
	t_color		*cell;
	int			height;
	int			width;
	char		**map;
}	t_map;

typedef struct s_player
{
	t_vec		*position;
	t_vec		*walk_dir;
	t_vec		*turn_dir;
	t_texture	*weapon;
	t_ray		*rays;
	int			fire;
	char		dir;
	float		fov_angle;
	float		rot_angle;
	float		walk_speed;
	float		turn_speed;
}	t_player;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	mlx_image_t	*minimap;
	mlx_image_t	*weapon;
	t_player	*player;
	t_interc	interct;
	t_interc	ray_inter_v;
	t_interc	ray_inter_h;
	double		last_time;
	double		current_time;
}	t_game;

// -------------------------- INITS ------------------------- //
t_game			*init_game(int ac, char **av);
t_map			*init_map();
t_player		*init_player(t_game *game);
t_ray			*init_rays(int nb_rays);
float			set_player_dir(char dir);
char			get_player_pos(char **map, t_vec *pos);


// ------------------------- RENDERS ------------------------ //
void			render_minimap_player(t_game *game);
void			render_minimap(t_game *game);
void			render_3d(t_game *game);
void			draw_walls(t_game *game, int pos_xy[2], t_vec wall_pixels);
mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray);
int				get_wall_texture_y(t_vec wall_pixels, int pos_y, mlx_texture_t *texture);
int				get_wall_texture_x(t_ray *ray, mlx_texture_t *texture);
t_vec			get_wall_position_pixels(float h_proj_wall);
void			draw_vertical_strip(t_game *game, int pos_xy[2], t_vec wall_pixels);
uint32_t		get_pixel(mlx_texture_t* texture, uint32_t x, uint32_t y);
void			put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);
void			draw_line(t_game *game, t_vec *start, t_vec *end, int color);
void			draw_line_mipmap(t_game *game, t_vec *start, t_vec *end, int color);
void			draw_rect(t_game *game, t_vec pos, t_vec size, int color);
void			draw_rect_mipmap(t_game *game, t_vec pos, t_vec size, int color);
int32_t			average_color(int start_color, int end_color, float f);
void			invert_color_mipmap(t_game *game, int x, int y, int *tilec);

// ------------------------ GAMELGCS ----------------------- //
void			game_routine(void *param);
void			input_handler(t_game *game);
void			move_player(t_game *game);
void			render(t_game *game);
void 			look_mouse(t_game *game);
void			key_hook(mlx_key_data_t keydata, void* param);
void			mouse_hook(mouse_key_t button, action_t action, \
					modifier_key_t mods, void* param);


// ------------------------ RAYS ----------------------- //
void			cast_all_rays(t_game *game);
void			cast_ray(t_game *game, float ray_angle, int ray_id);
int				is_in_map(t_game *game, t_vec pos);
int				get_collision(t_game *game, t_vec pos);
float			normalize_angle(float *angle);
float			distance_ab(t_vec a, t_vec b);
int				rgba2int(int r, int g, int b, int a);
void			horizontal_wall_hits(t_game *game);
void			horizontal_interc(t_game *game, float ray_angle);
void			vertical_wall_hits(t_game *game);
void			vertical_interc(t_game *game, float ray_angle);
void			reset_ray(t_interc *hv);
void			put_on_rays_struct(t_interc hv, t_game *game, int was_hit_v, int ray_id);
void			take_smallest_r_infos(t_game *game, float ray_angle, int ray_id);
int				get_at_map(t_game *game, float x, float y);
int				get_collision_door(t_game *game, t_vec pos);


// ------------------------- PARSING ------------------------ //
int				get_height(char **map);
int				get_width(char **map);
char			**parse(int argc, char **argv, t_game *game);
char			**ft_verif_map(char **map);
void			check_player_pos(t_game *game);
void			ft_skip_whitespace(char *line, int *i);
void			ft_skip_whitespace_newline(char *line, int *i);
void			ft_skip_number(char *line, int *i);
void			fill_first_line(char **map, char **new_map);
void			fill_first_space_line(char **map, char **new_map);
void			fill_last_line(char **map, char **new_map);
void			fill_last_space_line(char **map, char **new_map);
void			fill_line_border(char **map, char **new_map);
int				ft_map_length(char **map);
int				ft_find_big_line(char **map);
void			ft_check_n(char *line, t_game *game);
void			ft_check_s(char *line, t_game *game);
void			ft_check_w(char *line, t_game *game);
void			ft_check_e(char *line, t_game *game);
void			ft_check_empty_args(t_game *game);
void			ft_check_f_next(char **check, t_game *game, char *line);
void			ft_check_f(char *line, t_game *game);
void			ft_check_c_next(char **check, t_game *game, char *line);
void			ft_check_c(char *line, t_game *game);
void			ft_get_rgb(char *line, t_color *color, t_game *game);
void			ft_get_info_map(char *file, t_game *game);
void			ft_get_map(char *filename, char **map);
void			ft_check_texture(char *line, int i, t_game *game);
void			ft_check_rgb(char *line, int i, t_game *game);
void			ft_error(int msg, t_game *game);
void			ft_free(t_game *game);
void			ft_free2(t_game *game);
void			ft_free3(t_game *game);
void			ft_free_split(char **strs);

#endif
