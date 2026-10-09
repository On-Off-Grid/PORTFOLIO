/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:27:48 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:27:49 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_echo(const char *s1, const char *s2)
{
	if (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		while (*s1 == *s2 && *s1)
			s1++;
		if (!*s1)
			return (0);
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
