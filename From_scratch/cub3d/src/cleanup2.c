/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:04:43 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:05:16 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game);
	cleanup_map(game);
	free_textures_paths(game);
	cleanup_mlx(game);
}

void	cleanup_and_exit(t_game *game, int exit_code)
{
	cleanup_game(game);
	exit(exit_code);
}
