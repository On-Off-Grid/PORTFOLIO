/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:18:11 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:05 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	ft_memset(&ray, 0, sizeof(t_ray));
	render_floor_ceiling(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		calculate_wall_distance(&ray, game);
		calculate_line_height(&ray);
		calculate_draw_limits(&ray);
		determine_wall_face(&ray);
		calculate_wall_x(&ray, game);
		draw_wall_column(game, &ray, NULL, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.frame.img_ptr, 0, 0);
	return (1);
}

void	draw_wall_column(t_game *game, t_ray *ray, t_image *tex, int x)
{
	t_texture_draw	td;
	int				y;
	int				color;
	int				tex_x;
	int				tex_y;

	if (!tex)
		tex = select_texture(game, ray);
	tex_x = calculate_texture_x(ray, tex);
	init_texture_draw(&td, ray, tex);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)td.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		td.tex_pos += td.step;
		color = sample_texture(tex, tex_x, tex_y);
		put_pixel_to_image(&game->mlx.frame, x, y, color);
		y++;
	}
}

void	render_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	screen_mid;

	screen_mid = WINDOW_HEIGHT / 2;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < screen_mid)
				put_pixel_to_image(&game->mlx.frame, x, y,
					game->colors.ceiling_color);
			else
				put_pixel_to_image(&game->mlx.frame, x, y,
					game->colors.floor_color);
			x++;
		}
		y++;
	}
}
