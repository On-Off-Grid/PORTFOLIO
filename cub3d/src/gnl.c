/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:16:40 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:17:48 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define BUFFER_SIZE 4096

static char	*expand_buffer(char *buf, char *chunk, ssize_t len, ssize_t rd)
{
	char	*tmp;

	tmp = malloc(len + rd + 1);
	if (!tmp)
	{
		free(buf);
		return (NULL);
	}
	copy_buffers_gnl(tmp, buf, len);
	copy_buffers_gnl(tmp + len, chunk, rd);
	tmp[len + rd] = 0;
	free(buf);
	return (tmp);
}

static char	*read_all_gnl(int fd)
{
	char	*buf;
	ssize_t	rd;
	ssize_t	len;
	char	chunk[BUFFER_SIZE];

	buf = NULL;
	len = 0;
	rd = read(fd, chunk, BUFFER_SIZE);
	while (rd > 0)
	{
		buf = expand_buffer(buf, chunk, len, rd);
		if (!buf)
			return (NULL);
		len += rd;
		rd = read(fd, chunk, BUFFER_SIZE);
	}
	return (buf);
}

static void	reset_static(char **buf)
{
	free(*buf);
	*buf = NULL;
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	i;
	int			j;
	char		*line;

	if (!buf)
	{
		buf = read_all_gnl(fd);
		i = 0;
	}
	if (!buf || !buf[i])
	{
		reset_static(&buf);
		return (NULL);
	}
	j = i;
	while (buf[j] && buf[j] != '\n')
		j++;
	if (buf[j] == '\n')
		j++;
	line = strndup_gnl(buf + i, j - i);
	i = j;
	if (!buf[i])
		reset_static(&buf);
	return (line);
}
