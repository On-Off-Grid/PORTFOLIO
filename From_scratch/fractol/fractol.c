/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 08:27:52 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 12:08:24 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractol(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
	{
		printf("Error: Failed to initialize MiniLibX\n");
		exit(1);
	}
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fract'ol");
	if (!fractol->win)
	{
		free(fractol->mlx);
		printf("Error: Failed to create window\n");
		exit(1);
	}
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img.img)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol->mlx);
		printf("Error: Failed to create image\n");
		exit(1);
	}
	fractol->img.addr = mlx_get_data_addr(fractol->img.img,
			&fractol->img.bits_per_pixel, &fractol->img.line_length,
			&fractol->img.endian);
	fractol->x_min = -2.0;
	fractol->x_max = 2.0;
	fractol->y_min = -2.0;
	fractol->y_max = 2.0;
	fractol->color_shift = 0;
	fractol->max_iter = MAX_ITER;
}

int	parse_julia_params(int argc, char **argv, t_fractol *fractol)
{
	if (argc >= 4)
	{
		fractol->julia_c.real = ft_atof(argv[2]);
		fractol->julia_c.imag = ft_atof(argv[3]);
	}
	else
	{
		fractol->julia_c.real = -0.7;
		fractol->julia_c.imag = 0.27015;
	}
	return (1);
}

int	parse_arguments(int argc, char **argv, t_fractol *fractol)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol->fractal_type = MANDELBROT;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		fractol->fractal_type = JULIA;
		return (parse_julia_params(argc, argv, fractol));
	}
	else if (ft_strncmp(argv[1], "burning_ship", 13) == 0)
		fractol->fractal_type = BURNING_SHIP;
	else
		return (0);
	return (1);
}

void	print_usage(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════════════════╗\n");
	printf("║             Fract'ol Usage Instructions            ║\n");
	printf("╠════════════════════════════════════════════════════╣\n");
	printf("║ Available fractals:                                ║\n");
	printf("║  - mandelbrot                                      ║\n");
	printf("║  - julia [real] [imaginary]                        ║\n");
	printf("║    Example: ./fractol julia -0.7 0.27015           ║\n");
	printf("║  - burning_ship                                    ║\n");
	printf("║                                                    ║\n");
	printf("║ Controls:                                          ║\n");
	printf("║  - Arrow keys: Move the view                       ║\n");
	printf("║  - Mouse wheel: Zoom in/out                        ║\n");
	printf("║  - C key: Change color scheme                      ║\n");
	printf("║  - +/- keys: Increase/decrease maximum iterations  ║\n");
	printf("║  - ESC key: Exit program                           ║\n");
	printf("╚════════════════════════════════════════════════════╝\n");
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (!parse_arguments(argc, argv, &fractol))
	{
		print_usage();
		return (1);
	}
	init_fractol(&fractol);
	render_fractal(&fractol);
	mlx_hook(fractol.win, 2, 1L << 0, (int (*)())(void *)key_hook, &fractol);
	mlx_mouse_hook(fractol.win, (int (*)())(void *)mouse_hook, &fractol);
	mlx_hook(fractol.win, 17, 0, (int (*)())(void *)close_window, &fractol);
	mlx_loop(fractol.mlx);
	return (0);
}

