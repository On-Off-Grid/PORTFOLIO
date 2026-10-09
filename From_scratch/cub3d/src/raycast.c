/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:21:44 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 23:32:14 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->hit = 0;
	ray->side = 0;
	calculate_delta_dist(ray);
	calculate_step_and_side_dist(ray, game);
}

void	calculate_delta_dist(t_ray *ray)
{
	double	abs_dir_x;
	double	abs_dir_y;

	abs_dir_x = fabs(ray->ray_dir_x);
	abs_dir_y = fabs(ray->ray_dir_y);
	if (abs_dir_x < 1e-10)
		ray->delta_dist_x = DBL_MAX;
	else
		ray->delta_dist_x = 1.0 / abs_dir_x;
	if (abs_dir_y < 1e-10)
		ray->delta_dist_y = DBL_MAX;
	else
		ray->delta_dist_y = 1.0 / abs_dir_y;
}

void	calculate_step_and_side_dist(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	int	max_iter;
	int	iter_count;

	max_iter = game->map.width + game->map.height;
	iter_count = 0;
	while (ray->hit == 0 && iter_count < max_iter)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (check_wall_hit(ray, game))
			ray->hit = 1;
		iter_count++;
	}
}

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	double	g_offset;

	g_offset = (1 - ray->step_x) / 2.0;
	if (ray->side == 0)
	{
		if (fabs(ray->ray_dir_x) < 1e-10)
			ray->perp_wall_dist = DBL_MAX;
		else
			ray->perp_wall_dist = (ray->map_x - game->player.pos_x + g_offset)
				/ ray->ray_dir_x;
	}
	else
	{
		g_offset = (1 - ray->step_y) / 2.0;
		if (fabs(ray->ray_dir_y) < 1e-10)
			ray->perp_wall_dist = DBL_MAX;
		else
			ray->perp_wall_dist = (ray->map_y - game->player.pos_y + g_offset)
				/ ray->ray_dir_y;
	}
}
