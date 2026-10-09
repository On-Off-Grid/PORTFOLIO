/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:33:51 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:38:59 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == CHAR_WALL || c == CHAR_EMPTY || c == CHAR_SPACE || c == CHAR_NORTH
		|| c == CHAR_SOUTH || c == CHAR_WEST || c == CHAR_EAST)
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	if (c == CHAR_NORTH || c == CHAR_SOUTH || c == CHAR_EAST || c == CHAR_WEST)
		return (1);
	return (0);
}

int	check_player_spawn(t_game *game)
{
	if (!game->map.player_found)
		return (print_error("No player spawn found"), 0);
	return (1);
}

int	is_walkable_char(char c)
{
	if (c == CHAR_EMPTY || c == CHAR_NORTH || c == CHAR_SOUTH || c == CHAR_EAST
		|| c == CHAR_WEST)
		return (1);
	return (0);
}

void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
