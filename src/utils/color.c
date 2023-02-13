#include "../../inc/cub3D.h"

int	rgba2int(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	average_color(int start_color, int end_color, float f)
{
	int	new_color;
	int tmp;
	int i;

	i = 0;
	if (f < 0 || f > 1)
		return (start_color);
	new_color = 0;
	while (i < 4)
	{
		tmp = ((start_color >> (8 * i)) & 0xff) * f + ((end_color >> (8 * i)) & 0xff) * (1.0 - f);
		if (tmp > 255)
			tmp = 0;
		new_color += tmp << (i * 8);
		i++;
	}
	return (new_color);
}

float	distance_ab(t_vec a, t_vec b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
