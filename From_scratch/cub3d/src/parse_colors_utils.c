/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:27:47 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:29:43 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_color_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("Color value out of range (0-255)"), 0);
	return (1);
}

int	parse_color_component(char *str, int *i, int *value)
{
	int	start;

	skip_whitespace(str, i);
	if (!ft_isdigit(str[*i]))
		return (print_error("Invalid color format: expected digit"), 0);
	start = *i;
	while (ft_isdigit(str[*i]))
		(*i)++;
	*value = ft_atoi(str + start);
	return (1);
}

int	expect_comma(char *str, int *i)
{
	skip_whitespace(str, i);
	if (str[*i] != ',')
		return (print_error("Invalid color format: expected comma"), 0);
	(*i)++;
	return (1);
}
