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
typedef struct s_color t_color;

typedef struct s_color
{
}	t_color;

typedef struct s_vec
{

}	t_vec;

typedef struct s_map
{

}	t_map;

typedef struct s_player
{

}	t_player;


typedef struct s_game
{

}	t_game;


char	**parse(int argc, char **argv);
void	ft_verif_map(char **map);

#endif