/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:10:10 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:17:08 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	preprocess_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	is_map_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
		return (1);
	return (0);
}

void	free_map_lines(char **map_lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(map_lines[i++]);
	free(map_lines);
}

int	validate_all_elements(t_game *game)
{
	if (!game->textures.north_path || !game->textures.south_path
		|| !game->textures.west_path || !game->textures.east_path)
		return (print_error("Missing texture path"), 0);
	if (!game->colors.floor_set || !game->colors.ceiling_set)
		return (print_error("Missing floor or ceiling color"), 0);
	return (1);
}

void	skip_whitespace(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}
