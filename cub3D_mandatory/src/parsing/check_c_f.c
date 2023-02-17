/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:00:28 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 15:00:29 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_free_error(char *line, char **check, t_game *game)
{
	int	i;

	i = 0;
	free(line);
	while (check[i])
		free(check[i++]);
	free(check);
	ft_error(5, game);
}

void	ft_check_f_next(char **check, t_game *game, char *line)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (check[i])
	{
		j = 0;
		count = 0;
		while (check[i][j])
		{
			if (check[i][j] <= '9' && check[i][j] >= '0')
				count++;
			j++;
		}
		if (count == 0)
			ft_free_error(line, check, game);
		i++;
	}
	if (i != 3)
		ft_free_error(line, check, game);
}

void	ft_check_f(char *line, t_game *game)
{
	int		i;
	char	**check;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
	check = ft_split(&line[i], ',');
	if (check == NULL)
		ft_free_error(line, check, game);
	i = 0;
	ft_check_f_next(check, game, line);
	while (check[i])
	{
		free(check[i]);
		i++;
	}
	free(check);
}

void	ft_check_c_next(char **check, t_game *game, char *line)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	while (check[i])
	{
		j = 0;
		count = 0;
		while (check[i][j])
		{
			if (check[i][j] <= '9' && check[i][j] >= '0')
				count++;
			j++;
		}
		if (count == 0)
			ft_free_error(line, check, game);
		i++;
	}
	if (i != 3)
		ft_free_error(line, check, game);
}

void	ft_check_c(char *line, t_game *game)
{
	int		i;
	char	**check;

	i = 1;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
	check = ft_split(&line[i], ',');
	if (check == NULL)
		ft_free_error(line, check, game);
	i = 0;
	ft_check_c_next(check, game, line);
	while (check[i])
	{
		free(check[i]);
		i++;
	}
	free(check);
}
