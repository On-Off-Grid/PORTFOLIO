/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:58:58 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 22:05:09 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *  set the appropriate flag to the keycode of the event created by X11
 *    once it detects the hardware key press to 1.
 *
 *  @keycode: the keycode received by MLX when the function is called.
 *  @game: main game structure.
 *
 * */

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->player.move_forward = 1;
	if (keycode == KEY_S)
		game->player.move_backward = 1;
	if (keycode == KEY_A)
		game->player.move_left = 1;
	if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	return (0);
}

/*
 *  set the appropriate flag to the keycode of the event created by X11
 *    once it detects the hardware key release to 0.
 *
 *  @keycode: the keycode received by MLX when the function is called.
 *  @game: main game structure.
 *
 * */

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	if (keycode == KEY_S)
		game->player.move_backward = 0;
	if (keycode == KEY_A)
		game->player.move_left = 0;
	if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	return (0);
}

/*
 *  handle window closing event when X button is pressed
 *    by cleaning and exitting.
 *  @game: main game structure.
 *
 * */

int	handle_close(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

/*
 *  Register all event hooks for user input and window management.
 *  @game: main game structure.
 *
 * */

void	register_hooks(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, (int (*)())(void *)key_press_handler, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, (int (*)())(void *)key_release_handler, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, (int (*)())(void *)handle_close, game);
	mlx_loop_hook(game->mlx.mlx_ptr, (int (*)())(void *)game_loop, game);
}

