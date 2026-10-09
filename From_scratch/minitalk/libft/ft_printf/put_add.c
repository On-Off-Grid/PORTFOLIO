/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:38:07 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 09:48:46 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	add_hex(unsigned long long n)
{
	char	*hex_digits;
	int		l;

	hex_digits = "0123456789abcdef";
	l = 0;
	if (n >= 16)
		l += add_hex(n / 16);
	l += ft_putchar(hex_digits[n % 16]);
	return (l);
}

int	put_add(void *ptr)
{
	if (!ptr)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (add_hex((unsigned long long)ptr) + 2);
}
