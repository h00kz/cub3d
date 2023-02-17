/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubacqu <pdubacqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:59:56 by pdubacqu          #+#    #+#             */
/*   Updated: 2023/02/17 14:59:57 by pdubacqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	ft_free(t_game *game)
{
	free(game->ray_inter_v.interc);
	free(game->ray_inter_v.next_touch);
	free(game->ray_inter_v.to_check);
	free(game->ray_inter_v.step);
	free(game->ray_inter_h.interc);
	free(game->ray_inter_h.next_touch);
	free(game->ray_inter_h.to_check);
	free(game->ray_inter_h.step);
	free(game->map->wall_texture->s);
	free(game->map->wall_texture->n);
	free(game->map->wall_texture->e);
	free(game->map->wall_texture->w);
	free(game->map->wall_texture);
	free(game->map->map);
	free(game->map->floor);
	free(game->map->cell);
	free(game->map);
	free(game);
}

void	ft_free2(t_game *game)
{
	if (game->map->wall_texture->n->path)
		free(game->map->wall_texture->n->path);
	if (game->map->wall_texture->s->path)
		free(game->map->wall_texture->s->path);
	if (game->map->wall_texture->e->path)
		free(game->map->wall_texture->e->path);
	if (game->map->wall_texture->w->path)
		free(game->map->wall_texture->w->path);
	if (game->map->wall_texture->n->tex_img)
		mlx_delete_texture(game->map->wall_texture->n->tex_img);
	if (game->map->wall_texture->s->tex_img)
		mlx_delete_texture(game->map->wall_texture->s->tex_img);
	if (game->map->wall_texture->e->tex_img)
		mlx_delete_texture(game->map->wall_texture->e->tex_img);
	if (game->map->wall_texture->w->tex_img)
		mlx_delete_texture(game->map->wall_texture->w->tex_img);
	ft_free(game);
}

void	ft_free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
}

void	ft_free3(t_game *game)
{
	free(game->player->position);
	free(game->player->rays);
	free(game->player->turn_dir);
	free(game->player->walk_dir);
	free(game->player);
	ft_free_split(game->map->map);
	ft_free2(game);
}
