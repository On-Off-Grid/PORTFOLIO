/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:27:44 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 22:31:16 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *  applies forward vector to the provided coordinates, by multiplying
 *    the vector by the movement speed.
 *
 *  @game: main game structure.
 * */

void	handle_forward_movement(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.dir_x * game->player.move_speed;
	move_y = game->player.dir_y * game->player.move_speed;
	move_player(game, move_x, move_y);
}

/*
 *  applies backward vector to the provided coordinates, by multiplying
 *    the negative vector by the movement speed.
 *
 *  @game: main game structure.
 * */

void	handle_backward_movement(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = -game->player.dir_x * game->player.move_speed;
	move_y = -game->player.dir_y * game->player.move_speed;
	move_player(game, move_x, move_y);
}

/*
 *  apply strafing to the left by moving in opposite direction of plane vector,
 *    which is perpendicular to the direction vector.
 *
 *  @game: main game structure.
 *
 * */

void	handle_strafe_left(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = -game->player.plane_x * game->player.move_speed;
	move_y = -game->player.plane_y * game->player.move_speed;
	move_player(game, move_x, move_y);
}

/*
 *  apply strafing to the right by moving in direction of plane vector,
 *    which is perpendicular to the direction vector.
 *
 *  @game: main game structure.
 *
 * */

void	handle_strafe_right(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->player.plane_x * game->player.move_speed;
	move_y = game->player.plane_y * game->player.move_speed;
	move_player(game, move_x, move_y);
}
