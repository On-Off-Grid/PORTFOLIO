/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:05:39 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:45 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *  Rotate the player's view by a given angle (in radian), by rotating
 *    both the dir vector and camera plane together to keep them perpendicular
 *    using the standard 2d counterclockwise rotation matrix.
 *  @game: main game structure.
 *  @angle: rotation amount in radians, positive(right), otherwise(left).
 *
 * */

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	game->player.dir_x = game->player.dir_x * cos_a - game->player.dir_y
		* sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;
	game->player.plane_x = game->player.plane_x * cos_a - game->player.plane_y
		* sin_a;
	game->player.plane_y = old_plane_x * sin_a + game->player.plane_y * cos_a;
}

/*
 *  Apply movement with collision detection of each axis, allowing
 *    the player to slide along the walll.
 *
 *  @game: main game structure.
 *  @move_x: the change (delta) to apply on the X-axis
 *      (positive = right, negative = left).
 *  @move_y: the change (delta) to apply on the Y-axis
 *      (positive = downwards, negative = upwards)
 *
 *  return 1 if player moved on at least one axis, 0 if the player was
 *          blocked on both axis.
 * */

int	move_player(t_game *game, double move_x, double move_y)
{
	int		moved;
	double	buffer;

	moved = 0;
	buffer = COLLISION_BUFFER;
	if (try_move_x(game, move_x, buffer))
		moved = 1;
	if (try_move_y(game, move_y, buffer))
		moved = 1;
	return (moved);
}

/*
 *  process the movement input within the game loop.
 *
 *  @game: main game structure.
 * */

void	process_movement_input(t_game *game)
{
	if (game->player.move_forward)
		handle_forward_movement(game);
	if (game->player.move_backward)
		handle_backward_movement(game);
	if (game->player.move_left)
		handle_strafe_left(game);
	if (game->player.move_right)
		handle_strafe_right(game);
	if (game->player.rotate_left)
		rotate_player(game, -game->player.rot_speed);
	if (game->player.rotate_right)
		rotate_player(game, game->player.rot_speed);
}

/*
 *  the main game loop called continuously by MLX, it handles the game logic
 *    updates and rendering.
 *
 *  @game: main game structure.
 *  returns 0 to continue loop, non zero otherwise to stop.
 */

int	game_loop(t_game *game)
{
	process_movement_input(game);
	render_frame(game);
	return (0);
}
