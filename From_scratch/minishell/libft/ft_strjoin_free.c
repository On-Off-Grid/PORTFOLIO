/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:28:23 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:28:24 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_and_free(char *first, const char *second, char *dst)
{
	char	*p_first;
	size_t	len_first;

	len_first = ft_strlen(first);
	p_first = first;
	while (len_first--)
		*dst++ = *p_first++;
	free(first);
	while (*second)
		*dst++ = *second++;
	*dst = '\0';
}

char	*str_join_free(char *first, const char *second)
{
	size_t	len_first;
	size_t	len_second;
	char	*result;

	if (first)
		len_first = ft_strlen(first);
	else
		len_first = 0;
	len_second = ft_strlen(second);
	result = malloc(len_first + len_second + 1);
	if (!result)
		return (NULL);
	if (first)
		copy_and_free(first, second, result);
	else
		ft_strlcpy(result, second, len_second + 1);
	return (result);
}
