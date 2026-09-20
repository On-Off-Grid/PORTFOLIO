/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:28:18 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 23:37:32 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_wall_hit(t_ray *ray, t_game *game)
{
	if (ray->map_x < 0 || ray->map_x >= game->map.width || ray->map_y < 0
		|| ray->map_y >= game->map.height)
		return (1);
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	calculate_line_height(t_ray *ray)
{
	if (ray->perp_wall_dist == 0)
		ray->line_height = WINDOW_HEIGHT;
	else
		ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
}

void	calculate_draw_limits(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

int	determine_wall_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (WEST);
		return (EAST);
	}
	else
	{
		if (ray->step_y > 0)
			return (NORTH);
		return (SOUTH);
	}
}

void	calculate_wall_x(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
