/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:28:50 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:28:52 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Find last occurrence of character in string */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == c)
			last = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)last);
}
