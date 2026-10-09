/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:26:05 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:30:55 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_rgb_values(char *line, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	*r = 0;
	*g = 0;
	*b = 0;
	if (!parse_color_component(line, &i, r))
		return (0);
	if (!expect_comma(line, &i))
		return (0);
	if (!parse_color_component(line, &i, g))
		return (0);
	if (!expect_comma(line, &i))
		return (0);
	if (!parse_color_component(line, &i, b))
		return (0);
	if (!validate_color_range(*r, *g, *b))
		return (0);
	return (1);
}

int	parse_floor_color(char *line, t_game *game)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (game->colors.floor_set)
		return (print_error("Dup floor color"), 0);
	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!parse_rgb_values(line + i, &r, &g, &b))
		return (0);
	game->colors.floor_r = r;
	game->colors.floor_g = g;
	game->colors.floor_b = b;
	game->colors.floor_color = (r << 16) | (g << 8) | b;
	game->colors.floor_set = 1;
	return (1);
}

int	parse_ceiling_color(char *line, t_game *game)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (game->colors.ceiling_set)
		return (print_error("Dup ceiling color"), 0);
	i = 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!parse_rgb_values(line + i, &r, &g, &b))
		return (0);
	game->colors.ceiling_r = r;
	game->colors.ceiling_g = g;
	game->colors.ceiling_b = b;
	game->colors.ceiling_color = (r << 16) | (g << 8) | b;
	game->colors.ceiling_set = 1;
	return (1);
}
