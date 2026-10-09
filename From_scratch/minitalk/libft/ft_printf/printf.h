/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 05:37:58 by souichou          #+#    #+#             */
/*   Updated: 2025/01/11 05:59:03 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int	ft_putchar(int c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_puthex(unsigned int n);
int	put_add(void *ptr);
int	put_unsigned(unsigned int n);
int	upper_hex(unsigned int n);
int	format(char c, va_list args);
int	ft_printf(const char *last, ...);
#endif
