/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:22:36 by souichou          #+#    #+#             */
/*   Updated: 2024/11/14 16:29:58 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
	{
		if (*s == 45)
			sign = -sign;
		s++;
	}
	while (ft_isdigit(*s) == 1)
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}
/*
int main (int ac, char **av)
{
	if (ac == 2)
	{
		printf("my atoi: %d\n", ft_atoi(*(av + 1)));
		printf("standard atoi: %d\n", atoi(*(av + 1)));
	}
}*/
