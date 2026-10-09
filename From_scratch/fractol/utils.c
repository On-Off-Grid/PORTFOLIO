/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:28:17 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 11:30:10 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_complex	init_complex(double real, double imag)
{
	t_complex	complex;

	complex.real = real;
	complex.imag = imag;
	return (complex);
}

double	map(double value, double from_min, double from_max,
		double to_min, double to_max)
{
	return ((value - from_min) * (to_max - to_min)
		/ (from_max - from_min) + to_min);
}

int	close_window(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(0);
	return (0);
}

