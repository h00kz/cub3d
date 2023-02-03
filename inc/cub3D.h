#ifndef CUB3D_HPP
# define CUB3D_HPP

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// ----------------------- STRUCTS ------------------------- //
typedef struct s_game t_game;
typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_vec t_vec;
typedef struct s_texture t_texture;
typedef struct s_wall t_wall;
typedef struct s_color t_color;

typedef struct s_texture
{
	char	*path;
}	t_texture;

typedef struct s_wall
{
	t_texture	*N;
	t_texture	*S;
	t_texture	*E;
	t_texture	*W;
}			t_wall;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}		t_color;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}			t_vec;

typedef struct s_map
{
	t_wall		**wall_texture;
	t_color		*floor;
	t_color		*cell;
	char		**map;
}				t_map;

typedef struct s_player
{
	t_vec	*position;
	t_vec	*direction;
	float	angle;
}			t_player;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	t_player	*player;
}				t_game;
// ---------------------------------------------------------- //

// ------------------------- PARSING ------------------------ //
char	**parse(int argc, char **argv);
void	ft_verif_map(char **map);
// ---------------------------------------------------------- //

#endif