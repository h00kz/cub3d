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
# define WIN_HALF_W (floor(WIN_WIDTH / 2))
# define WIN_HEIGHT 900
# define WIN_HALF_H (floor(WIN_HEIGHT / 2))
# define MAP_TILE 64
# define MINIMAP_SCALE_FACTOR 1
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
	mlx_image_t	tex_img;
	t_vec		*size;
	t_vec		*pos;
	char		*path;
}	t_texture;

typedef struct s_wall
{
	t_texture	*N;
	t_texture	*S;
	t_texture	*E;
	t_texture	*W;
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
	t_vec	*position;
	t_vec	*walk_dir;
	t_vec	*turn_dir;
	t_ray	*rays;
	float	fov_angle;
	float	rot_angle;
	float	walk_speed;
	float	turn_speed;
	int		minimap_w;
	int		minimap_h;
}	t_player;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	mlx_image_t	*minimap;
	t_player	*player;
	t_interc	interct;
	t_interc	ray_inter_v;
	t_interc	ray_inter_h;
	int			debug_render_rays;
	double		last_time;
	double		current_time;
	int			frame_count;
}	t_game;

// -------------------------- INITS ------------------------- //
t_game		*init_game();
t_map		*init_map();
t_player	*init_player();
t_ray		*init_rays(int nb_rays);

// ------------------------- RENDERS ------------------------ //
void		render_minimap_player(t_game *game);
void		render_ray(t_game *game);
void		render_3d(t_game *game);
void		render_minimap(t_game *game);
void		put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);
void		draw_line(t_game *game, t_vec *start, t_vec *end, int color);
void		draw_rect(t_game *game, t_vec pos, t_vec size, int color);


// ------------------------ GAMELGCS ----------------------- //
void		input_handler(t_game *game);
void		move_player(t_game *game);
void		update(t_game *game);
void		render(t_game *game);

// ------------------------ RAYS ----------------------- //
void		cast_all_rays(t_game *game);

int			is_in_map(t_vec pos);
int			get_collision(t_game *game, t_vec pos);
float		normalize_angle(float *angle);
float		distance_ab(t_vec a, t_vec b);
int			rgba2int(int r, int g, int b, int a);

// ------------------------- PARSING ------------------------ //

char		**parse(int argc, char **argv, t_game *game);
char		**ft_verif_map(char **map);
void		check_player_pos(char **map);

#endif