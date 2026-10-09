/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*strndup_gnl(const char *s, int n)
{
	char	*res;
	int		i;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[n] = 0;
	return (res);
}

void	copy_buffers_gnl(char *dst, char *src, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}
