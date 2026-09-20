/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:43:58 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:59:51 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Load individual texture from file using MLX helper functions.
 *
 * @mlx: MLX structure containing context.
 * @img: Destination image structure.
 * @path: path to the corresponding texture file.
 *
 * returns 1 on success, 0 otherwise.
 * */

int	load_texture(t_mlx *mlx, t_image *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img->width,
			&img->height);
	if (!img->img_ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (0);
	return (validate_texture_size(img));
}

/*
 * Load all textures (N, S, E, W) using MLX helpers.
 *
 * @game: main game structure.
 * returns 1 on success, 0 otherwise.
 */

int	load_all_textures(t_game *game)
{
	if (!load_texture(&game->mlx, &game->textures.north,
			game->textures.north_path))
		return (print_error("Failed to load north texture"), 0);
	if (!load_texture(&game->mlx, &game->textures.south,
			game->textures.south_path))
		return (print_error("Failed to load south texture"), 0);
	if (!load_texture(&game->mlx, &game->textures.east,
			game->textures.east_path))
		return (print_error("Failed to load east texture"), 0);
	if (!load_texture(&game->mlx, &game->textures.west,
			game->textures.west_path))
		return (print_error("Failed to load west texture"), 0);
	return (1);
}

/* Initializes player default values and vectors
 *
 *  @game: main game structure.
 *
 *  returns 1 on success, 0 otherwise.
 */

int	init_player(t_game *game)
{
	if (!game->map.player_found)
		return (print_error("No player position found."), 0);
	set_player_direction(game, game->map.player_dir);
	calculate_plane_vector(game);
	set_movement_speed(game);
	game->player.move_forward = 0;
	game->player.move_backward = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
	return (1);
}

/*
 * Initializes texture structures and load image files.
 * @game: main game structure.
 *
 *  returns 1 on success, 0 otherwise.
 */

int	init_textures(t_game *game)
{
	if (!load_all_textures(game))
		return (0);
	return (1);
}

int	init_game_state(t_game *game)
{
	if (!init_player(game))
		return (0);
	if (!init_textures(game))
		return (0);
	init_colors(game);
	game->initialized = 1;
	return (1);
}
