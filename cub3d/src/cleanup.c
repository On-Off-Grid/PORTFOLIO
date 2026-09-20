/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:03:58 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:04:39 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_texture(t_mlx *mlx, t_image *img)
{
	if (img && img->img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}

void	cleanup_textures(t_game *game)
{
	destroy_texture(&game->mlx, &game->textures.north);
	destroy_texture(&game->mlx, &game->textures.south);
	destroy_texture(&game->mlx, &game->textures.east);
	destroy_texture(&game->mlx, &game->textures.west);
}

void	cleanup_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i])
			free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void	free_textures_paths(t_game *game)
{
	if (game->textures.north_path)
		free(game->textures.north_path);
	if (game->textures.south_path)
		free(game->textures.south_path);
	if (game->textures.east_path)
		free(game->textures.east_path);
	if (game->textures.west_path)
		free(game->textures.west_path);
	game->textures.north_path = NULL;
	game->textures.south_path = NULL;
	game->textures.east_path = NULL;
	game->textures.west_path = NULL;
}

void	cleanup_mlx(t_game *game)
{
	if (game->mlx.frame.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.frame.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
}
