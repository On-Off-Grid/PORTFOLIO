/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:48:42 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:54:49 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * sets the player's direction vector based on spawn orientation character.
 * @game: main game structure.
 * @dir: char indicating direction (N, S, W, E).
 *
 */

void	set_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

/*
 * Calculates ca,era plane vector from direction and FOV, The plane vector is
 *  perpendicular to the direction vector, it's magnitude is calculated based
 *  on FOV to define the field of view, by using tan(FOV/2) to ensure proper
 *  perspective projection..
 *
 * @game: main game structure.
 */

void	calculate_plane_vector(t_game *game)
{
	double	fov_radians;
	double	plane_magnitude;

	fov_radians = FOV * (M_PI / 180.0);
	plane_magnitude = tan(fov_radians / 2.0);
	game->player.plane_x = -game->player.dir_y * plane_magnitude;
	game->player.plane_y = game->player.dir_x * plane_magnitude;
}

/*
 *  sets movement and rotation speed for player.
 * */

void	set_movement_speed(t_game *game)
{
	game->player.move_speed = MOVE_SPEED;
	game->player.rot_speed = ROT_SPEED;
}

/*
 *  converts RGB int components (0-255) to to MLX integer color (0-255).
 *
 *  @r: Red.
 *  @g: Green.
 *  @b: Blue
 *  returns: Integer color (combining r, g and blue.)
 * */

int	rgb_to_mlx_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/*
 *  Initializes floor and ceiling colors by converting RGB to MLX colors.
 *  @game: main game structure.
 *
 * */
void	init_colors(t_game *game)
{
	game->colors.floor_color = rgb_to_mlx_color(game->colors.floor_r,
			game->colors.floor_g, game->colors.floor_b);
	game->colors.ceiling_color = rgb_to_mlx_color(game->colors.ceiling_r,
			game->colors.ceiling_g, game->colors.ceiling_b);
}
