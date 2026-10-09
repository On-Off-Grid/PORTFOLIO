/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:28:16 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:28:17 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_str(char *dest, const char *src, size_t offset)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[offset + i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	copy_str(result, s1, 0);
	copy_str(result, s2, len1);
	result[len1 + len2] = '\0';
	return (result);
}
