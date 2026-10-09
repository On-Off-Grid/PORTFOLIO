/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	finalize_map(t_game *game, char **map_lines, int map_count)
{
	int	i;
	int	max_width;

	game->map.grid = malloc(sizeof(char *) * (map_count + 1));
	if (!game->map.grid)
		return (0);
	max_width = 0;
	i = 0;
	while (i < map_count)
	{
		game->map.grid[i] = ft_strdup(map_lines[i]);
		if (!game->map.grid[i])
			return (0);
		if (ft_strlen(game->map.grid[i]) > max_width)
			max_width = ft_strlen(game->map.grid[i]);
		free(map_lines[i]);
		i++;
	}
	game->map.grid[i] = NULL;
	game->map.height = map_count;
	game->map.width = max_width;
	return (1);
}

int	validate_texture_size(t_image *img)
{
	if (img->width <= 0 || img->height <= 0)
		return (0);
	return (1);
}
