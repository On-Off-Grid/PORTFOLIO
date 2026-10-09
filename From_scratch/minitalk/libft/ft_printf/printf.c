/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:37:48 by souichou          #+#    #+#             */
/*   Updated: 2025/01/11 14:01:19 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (put_unsigned(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_puthex(va_arg(args, unsigned int)));
	if (c == 'X')
		return (upper_hex(va_arg(args, unsigned int)));
	if (c == 'p')
		return (put_add(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *last, ...)
{
	int		count;
	va_list	args;

	va_start(args, last);
	count = 0;
	if (!last)
		return (-1);
	while (*last)
	{
		if (*last == 37)
		{
			last++;
			if (*last == 0)
				return (-1);
			else if (*last == 37)
				count += ft_putchar(37);
			count += format(*last, args);
		}
		else
			count += ft_putchar(*last);
		last++;
	}
	return (count);
}
/*#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int x = ft_printf("int : %x %x // %x // %x %%", LONG_MIN, LONG_MAX
	, INT_MIN, INT_MAX);
	printf("\n");
	int y = printf("int : %x %x // %x // %x %%", LONG_MIN, LONG_MAX
	, INT_MIN, INT_MAX);
	printf("\n %d---------%d \n", x, y);
	printf("***************************\n");
	int a = ft_printf("int : %p %p // %p // %p %%", LONG_MIN, LONG_MAX
	, INT_MIN, INT_MAX);
	printf("\n");
	int b = printf("int : %p %p // %p // %p %%", LONG_MIN, LONG_MAX
	, INT_MIN, INT_MAX);
	printf("\n %d---------%d \n", a, b);
	
}*/
