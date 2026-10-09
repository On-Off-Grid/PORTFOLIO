/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:28:06 by souichou          #+#    #+#             */
/*   Updated: 2025/04/04 02:39:34 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
# define ZOOM_FACTOR 0.9
# define MOVE_FACTOR 0.05

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65362
# define KEY_UP 65364
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEY_C 99

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			fractal_type;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	t_complex	julia_c;
	int			color_shift;
	int			max_iter;
}	t_fractol;

/* Main functions */
void		init_fractol(t_fractol *fractol);
int			parse_arguments(int argc, char **argv, t_fractol *fractol);
void		render_fractal(t_fractol *fractol);

/* Fractal calculation functions */
int			mandelbrot_iter(t_complex c, int max_iter);
int			julia_iter(t_complex z, t_complex c, int max_iter);
int			burning_ship_iter(t_complex c, int max_iter);

/* Color functions */
int			get_color(int iterations, int max_iter, int color_shift);
int			create_rgb(int r, int g, int b);
void		hsv_to_rgb(double h, double s, double v, int *r, int *g, int *b);

/* Utility functions */
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_complex	init_complex(double real, double imag);
double		map(double value, double from_min, double from_max, 
				double to_min, double to_max);
double		ft_atof(const char *str);

/* Event handling functions */
int			key_hook(int keycode, t_fractol *fractol);
int			mouse_hook(int button, int x, int y, t_fractol *fractol);
int			close_window(t_fractol *fractol);
void		print_usage(void);

/* Rendering helpers */
void		calculate_point(t_fractol *fractol, int x, int y);

#endif

