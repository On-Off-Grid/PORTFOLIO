/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:03:06 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:01:51 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * check whether filename ends with .cub extension.
 * @filename: string to check (filename).
 *
 * returns 1 if valid, 0 otherwise.
 */

int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

/*
 * validates command line arguments, must be one (.cub path).
 * @ac: args count.
 * @av: args vector.
 * returns 1 if valid, 0 if invalid.
 *
 */

int	validate_arguments(int ac, char **av)
{
	if (ac != 2)
		return (print_error("Usage: ./cub3d <path_to_map.cub>"), 0);
	if (!av[1] || !*av[1])
		return (print_error("Invalid argument."), 0);
	if (!check_file_extension(av[1]))
		return (print_error("Invalid file extension. Must be .cub."), 0);
	return (1);
}

/*
 * Creates the game window with the specified dimensions.
 * @game: main game structure.
 *
 * returns 1 on success, 0 otherwise.
 */

int	setup_window(t_game *game)
{
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!game->mlx.win_ptr)
		return (0);
	return (1);
}

/*
 * Initialize MLX lib and create a window.
 *  @game: Main game structure.
 *
 * return 1 on success, 0 otherwise.
 */

int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (0);
	if (!setup_window(game))
		return (0);
	game->mlx.frame.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!game->mlx.frame.img_ptr)
		return (0);
	game->mlx.frame.addr = mlx_get_data_addr(game->mlx.frame.img_ptr,
			&game->mlx.frame.bits_per_pixel, &game->mlx.frame.line_length,
			&game->mlx.frame.endian);
	game->mlx.frame.width = WINDOW_WIDTH;
	game->mlx.frame.height = WINDOW_HEIGHT;
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (!validate_arguments(ac, av))
		return (1);
	if (!parse_config_file(av[1], &game))
		return (exit_with_error(&game, "Failed to parse configuration file"),
			1);
	if (!validate_map(&game))
		return (exit_with_error(&game, "Invalid map configuration"), 1);
	if (!init_mlx(&game))
		return (exit_with_error(&game, "Failed to initialize MLX"), 1);
	if (!init_game_state(&game))
		return (exit_with_error(&game, "Failed to initialize game state"), 1);
	register_hooks(&game);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	return (0);
}
