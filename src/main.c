#include "../inc/cub3D.h"

int main(int argc, char **argv)
{
	char **map;

	map = parse(argc, argv);
	ft_verif_map(map);

}