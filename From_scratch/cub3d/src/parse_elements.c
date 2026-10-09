/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:06:23 by souichou          #+#    #+#             */
/*   Updated: 2026/01/21 21:14:42 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_element_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (1);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_texture_north(line + i, game));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_texture_south(line + i, game));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_texture_west(line + i, game));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_texture_east(line + i, game));
	else if (line[i] == 'F')
		return (parse_floor_color(line + i, game));
	else if (line[i] == 'C')
		return (parse_ceiling_color(line + i, game));
	else if (line[i] == '1' || line[i] == '0')
		return (1);
	return (print_error("Unknown indentifier in config file"), 0);
}

static int	process_element(char *line, t_game *game, char **map_lines,
		int map_count)
{
	if (ft_strlen(line) > 0)
	{
		if (!parse_element_line(line, game))
		{
			free(line);
			free_map_lines(map_lines, map_count);
			return (0);
		}
	}
	free(line);
	return (1);
}

static int	parse_file_lines(int fd, t_game *game, char **map_lines,
		int *in_map)
{
	char	*line;
	int		map_count;

	map_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		preprocess_line(line);
		if (!*in_map && is_map_line(line))
			*in_map = 1;
		if (*in_map)
			map_lines[map_count++] = line;
		else
		{
			if (!process_element(line, game, map_lines, map_count))
			{
				drain_gnl(fd);
				return (-1);
			}
		}
		line = get_next_line(fd);
	}
	return (map_count);
}

int	read_and_parse(int fd, t_game *game)
{
	char	**map_lines;
	int		map_count;
	int		in_map;

	map_lines = malloc(sizeof(char *) * 1000);
	if (!map_lines)
		return (0);
	in_map = 0;
	map_count = parse_file_lines(fd, game, map_lines, &in_map);
	if (map_count == -1)
		return (0);
	if (map_count > 0)
	{
		if (!finalize_map(game, map_lines, map_count))
			return (0);
	}
	free(map_lines);
	return (1);
}

int	parse_config_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error("Could not open config. file");
		return (-1);
	}
	if (fd == -1)
		return (0);
	if (!read_and_parse(fd, game))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!validate_all_elements(game))
		return (0);
	return (1);
}
