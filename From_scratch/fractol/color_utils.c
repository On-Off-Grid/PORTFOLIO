/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:28:17 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 11:30:10 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	hsv_to_rgb_part1(double h, double c, double x, double rgb[3])
{
	if (h >= 0 && h < 60)
	{
		rgb[0] = c;
		rgb[1] = x;
		rgb[2] = 0;
	}
	else if (h >= 60 && h < 120)
	{
		rgb[0] = x;
		rgb[1] = c;
		rgb[2] = 0;
	}
	else if (h >= 120 && h < 180)
	{
		rgb[0] = 0;
		rgb[1] = c;
		rgb[2] = x;
	}
}

void	hsv_to_rgb_part2(double h, double c, double x, double rgb[3])
{
	if (h >= 180 && h < 240)
	{
		rgb[0] = 0;
		rgb[1] = x;
		rgb[2] = c;
	}
	else if (h >= 240 && h < 300)
	{
		rgb[0] = x;
		rgb[1] = 0;
		rgb[2] = c;
	}
	else
	{
		rgb[0] = c;
		rgb[1] = 0;
		rgb[2] = x;
	}
}

void	hsv_to_rgb(double h, double s, double v, int *r, int *g, int *b)
{
	double	c;
	double	x;
	double	m;
	double	rgb[3];

	c = v * s;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	m = v - c;
	if (h < 180)
		hsv_to_rgb_part1(h, c, x, rgb);
	else
		hsv_to_rgb_part2(h, c, x, rgb);
	*r = (rgb[0] + m) * 255;
	*g = (rgb[1] + m) * 255;
	*b = (rgb[2] + m) * 255;
}

int	get_color(int iterations, int max_iter, int color_shift)
{
	double	t;
	int		r;
	int		g;
	int		b;
	double	h;

	if (iterations == max_iter)
		return (0);
	t = (double)iterations / (double)max_iter;
	h = 360.0 * t + color_shift;
	while (h >= 360.0)
		h -= 360.0;
	hsv_to_rgb(h, 1.0, t < 0.5 ? t * 2 : 1.0, &r, &g, &b);
	return (create_rgb(r, g, b));
}

