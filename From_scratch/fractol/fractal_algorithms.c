/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_algorithms.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:27:41 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 11:29:00 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_iter(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	while (i < max_iter)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

int	julia_iter(t_complex z, t_complex c, int max_iter)
{
	int			i;
	double		temp;

	i = 0;
	while (i < max_iter)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

int	burning_ship_iter(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	while (i < max_iter)
	{
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		z.real = fabs(z.real);
		z.imag = fabs(z.imag);
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		i++;
	}
	return (i);
}

void	calculate_point(t_fractol *fractol, int x, int y)
{
	t_complex	c;
	t_complex	z;
	int			iterations;

	c.real = fractol->x_min + (x * (fractol->x_max - fractol->x_min) / WIDTH);
	c.imag = fractol->y_max - (y * (fractol->y_max - fractol->y_min) / HEIGHT);
	if (fractol->fractal_type == MANDELBROT)
		iterations = mandelbrot_iter(c, fractol->max_iter);
	else if (fractol->fractal_type == JULIA)
	{
		z.real = c.real;
		z.imag = c.imag;
		iterations = julia_iter(z, fractol->julia_c, fractol->max_iter);
	}
	else
		iterations = burning_ship_iter(c, fractol->max_iter);
	my_mlx_pixel_put(&fractol->img, x, y,
		get_color(iterations, fractol->max_iter, fractol->color_shift));
}

void	render_fractal(t_fractol *fractol)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_point(fractol, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

