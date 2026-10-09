/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:38:34 by souichou          #+#    #+#             */
/*   Updated: 2025/01/11 14:00:29 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	upper_hex(unsigned int n)
{
	char	*hex_digits;
	int		l;

	hex_digits = "0123456789ABCDEF";
	l = 0;
	if (n >= 16)
		l += upper_hex(n / 16);
	l += ft_putchar(hex_digits[n % 16]);
	return (l);
}
