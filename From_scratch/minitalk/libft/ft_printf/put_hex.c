/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:38:16 by souichou          #+#    #+#             */
/*   Updated: 2025/01/11 14:00:03 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_puthex(unsigned int n)
{
	char	*hex_digits;
	int		l;

	hex_digits = "0123456789abcdef";
	l = 0;
	if (n >= 16)
		l += ft_puthex(n / 16);
	l += ft_putchar(hex_digits[n % 16]);
	return (l);
}
