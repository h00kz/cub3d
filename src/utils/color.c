#include "../../inc/cub3D.h"

int	rgba2int(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

float	distance_ab(t_vec a, t_vec b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
