/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_management_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:21:44 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 23:06:29 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * updates the factor flag depending on the sign of the deltas.
 *
 * @delta: change to apply to the apropriate axis.
 * @sign:
 * */

void	update_factor(double delta, int *sign)
{
	if (delta > 0)
		*sign = 1;
	else
		*sign = -1;
}

/*
 * check map grid for wall collision by adding a tiny buffer to the coordinates
 *  before casting the to integers.
 *
 * @game: main game structure.
 * @x: x_axis coordinates.
 * @y: y_axis coordinates.
 *
 * return 1 if there's a collision or out of bounds, 0 otherwise.
 * */

int	check_wall_collision(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_x >= game->map.width || grid_y < 0
		|| grid_y >= game->map.height)
		return (1);
	if (game->map.grid[grid_y][grid_x] == '1')
		return (1);
	return (0);
}

int	try_move_x(t_game *game, double move_x, double buffer)
{
	double	new_x;
	int		factor;

	factor = 0;
	new_x = game->player.pos_x + move_x;
	update_factor(move_x, &factor);
	if (!check_wall_collision(game, new_x + buffer * factor,
			game->player.pos_y))
	{
		game->player.pos_x = new_x;
		return (1);
	}
	return (0);
}

int	try_move_y(t_game *game, double move_y, double buffer)
{
	double	new_y;
	int		factor;

	factor = 0;
	new_y = game->player.pos_y + move_y;
	update_factor(move_y, &factor);
	if (!check_wall_collision(game, game->player.pos_x, new_y + buffer
			* factor))
	{
		game->player.pos_y = new_y;
		return (1);
	}
	return (0);
}
