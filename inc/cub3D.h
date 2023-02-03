#ifndef CUB3D_HPP
#define CUB3D_HPP

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

char	**parse(int argc, char **argv);
void	ft_verif_map(char **map);

#endif