/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:23:32 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:25:56 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture_north(char *line, t_game *game)
{
	int	i;
	int	len;

	if (game->textures.north_path)
		return (print_error("Dup NO texture"), 0);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (print_error("Missing path for NO texture"), 0);
	game->textures.north_path = ft_strdup(line + i);
	len = ft_strlen(game->textures.north_path);
	if (len > 0 && game->textures.north_path[len - 1] == '\n')
		game->textures.north_path[len - 1] = '\0';
	return (1);
}

int	parse_texture_south(char *line, t_game *game)
{
	int	i;
	int	len;

	if (game->textures.south_path)
		return (print_error("Dup SO texture"), 0);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (print_error("Missing path for SO texture"), 0);
	game->textures.south_path = ft_strdup(line + i);
	len = ft_strlen(game->textures.south_path);
	if (len > 0 && game->textures.south_path[len - 1] == '\n')
		game->textures.south_path[len - 1] = '\0';
	return (1);
}

int	parse_texture_west(char *line, t_game *game)
{
	int	i;
	int	len;

	if (game->textures.west_path)
		return (print_error("Dup WE texture"), 0);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (print_error("Missing path for WE texture"), 0);
	game->textures.west_path = ft_strdup(line + i);
	len = ft_strlen(game->textures.west_path);
	if (len > 0 && game->textures.west_path[len - 1] == '\n')
		game->textures.west_path[len - 1] = '\0';
	return (1);
}

int	parse_texture_east(char *line, t_game *game)
{
	int	i;
	int	len;

	if (game->textures.east_path)
		return (print_error("Dup EA texture"), 0);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (print_error("Missing path for EA texture"), 0);
	game->textures.east_path = ft_strdup(line + i);
	len = ft_strlen(game->textures.east_path);
	if (len > 0 && game->textures.east_path[len - 1] == '\n')
		game->textures.east_path[len - 1] = '\0';
	return (1);
}
