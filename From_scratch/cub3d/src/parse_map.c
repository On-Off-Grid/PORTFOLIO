/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:31:53 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:38:03 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_cell_enclosed(t_game *game, int x, int y)
{
	int	row_l;

	if (y <= 0 || y >= game->map.height - 1)
		return (0);
	if (x <= 0)
		return (0);
	row_l = ft_strlen(game->map.grid[y]);
	if (x >= row_l - 1)
		return (0);
	if (game->map.grid[y][x - 1] == CHAR_SPACE)
		return (0);
	if (game->map.grid[y][x + 1] == CHAR_SPACE)
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y - 1]) || game->map.grid[y
			- 1][x] == CHAR_SPACE)
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y + 1]) || game->map.grid[y
			+ 1][x] == CHAR_SPACE)
		return (0);
	return (1);
}

int	check_map_enclosed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (is_walkable_char(game->map.grid[y][x]))
			{
				if (!check_cell_enclosed(game, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	find_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (is_player_char(game->map.grid[y][x]))
			{
				if (game->map.player_found)
					return (print_error("Multiple player spawns"), 0);
				game->map.player_found = 1;
				game->map.player_dir = game->map.grid[y][x];
				game->map.player_x = x;
				game->map.player_y = y;
				game->player.pos_x = (double)x + 0.5;
				game->player.pos_y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (!is_valid_map_char(game->map.grid[y][x]))
				return (print_error("Invalid character in map"), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_map_characters(game))
		return (0);
	if (!find_player_position(game))
		return (0);
	if (!check_player_spawn(game))
		return (0);
	if (!check_map_enclosed(game))
		return (print_error("Map is not enclosed by walls"), 0);
	return (1);
}
