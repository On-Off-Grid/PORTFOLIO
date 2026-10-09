/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:38:25 by souichou          #+#    #+#             */
/*   Updated: 2025/01/11 14:00:19 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	put_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += put_unsigned(n / 10);
	count += ft_putchar(n % 10 + 48);
	return (count);
}
