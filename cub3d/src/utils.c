/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:07:32 by souichou          #+#    #+#             */
/*   Updated: 2026/01/22 00:08:27 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

int	print_error(char *message)
{
	write(2, "Error\n", 6);
	if (message)
		write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (1);
}

void	exit_with_error(t_game *game, char *message)
{
	print_error(message);
	cleanup_game(game);
	exit(1);
}

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
