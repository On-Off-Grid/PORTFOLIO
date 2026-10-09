/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:55:28 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 23:56:52 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	sample_texture(t_image *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (get_pixel_from_image(texture, x, y));
}

void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_from_image(t_image *img, int x, int y)
{
	char	*src;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	src = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}
