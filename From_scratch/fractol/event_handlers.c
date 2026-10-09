/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:28:17 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 11:30:10 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_arrow_keys(int keycode, t_fractol *fractol)
{
	double	range_x;
	double	range_y;
	double	move_factor;

	range_x = fractol->x_max - fractol->x_min;
	range_y = fractol->y_max - fractol->y_min;
	move_factor = 0.05;
	if (keycode == KEY_LEFT)
	{
		fractol->x_min -= range_x * move_factor;
		fractol->x_max -= range_x * move_factor;
	}
	else if (keycode == KEY_RIGHT)
	{
		fractol->x_min += range_x * move_factor;
		fractol->x_max += range_x * move_factor;
	}
	else if (keycode == KEY_UP)
	{
		fractol->y_min -= range_y * move_factor;
		fractol->y_max -= range_y * move_factor;
	}
	else if (keycode == KEY_DOWN)
	{
		fractol->y_min += range_y * move_factor;
		fractol->y_max += range_y * move_factor;
	}
}

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		return (close_window(fractol));
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		handle_arrow_keys(keycode, fractol);
	else if (keycode == KEY_C)
		fractol->color_shift = (fractol->color_shift + 60) % 360;
	else if (keycode == KEY_PLUS)
		fractol->max_iter += 10;
	else if (keycode == KEY_MINUS && fractol->max_iter > 10)
		fractol->max_iter -= 10;
	render_fractal(fractol);
	return (0);
}

void	apply_zoom(t_fractol *fractol, int x, int y, double zoom_factor)
{
	double	mouse_x;
	double	mouse_y;

	mouse_x = fractol->x_min + (x * (fractol->x_max - fractol->x_min) / WIDTH);
	mouse_y = fractol->y_max - (y * (fractol->y_max - fractol->y_min) / HEIGHT);
	fractol->x_min = mouse_x + (fractol->x_min - mouse_x) * zoom_factor;
	fractol->x_max = mouse_x + (fractol->x_max - mouse_x) * zoom_factor;
	fractol->y_min = mouse_y + (fractol->y_min - mouse_y) * zoom_factor;
	fractol->y_max = mouse_y + (fractol->y_max - mouse_y) * zoom_factor;
}

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;

	zoom_factor = 1.0;
	if (button == 4)
		zoom_factor = 0.9;
	else if (button == 5)
		zoom_factor = 1.1;
	if (button == 4 || button == 5)
	{
		apply_zoom(fractol, x, y, zoom_factor);
		render_fractal(fractol);
	}
	return (0);
}

