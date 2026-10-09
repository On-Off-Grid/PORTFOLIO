/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:48:18 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 02:42:59 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_image	*select_texture(t_game *game, t_ray *ray)
{
	int	face;

	face = determine_wall_face(ray);
	if (face == NORTH)
		return (&game->textures.north);
	else if (face == SOUTH)
		return (&game->textures.south);
	else if (face == EAST)
		return (&game->textures.east);
	else
		return (&game->textures.west);
}

int	calculate_texture_x(t_ray *ray, t_image *texture)
{
	int	tex_x;
	int	needs_flip;

	tex_x = (int)(ray->wall_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	needs_flip = ((ray->side == 0 && ray->ray_dir_x > 0)
			|| (ray->side == 1 && ray->ray_dir_y < 0));
	if (needs_flip)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	init_texture_draw(t_texture_draw *tex, t_ray *ray, t_image *img)
{
	double	screen_center;

	if (ray->line_height == 0)
		tex->step = 0;
	else
		tex->step = (double)img->height / (double)ray->line_height;
	screen_center = (double)WINDOW_HEIGHT / 2.0;
	tex->tex_pos = (ray->draw_start - screen_center + ray->line_height / 2.0)
		* tex->step;
}
