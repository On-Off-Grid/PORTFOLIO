/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:11:37 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 12:07:21 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int	ft_strlen(const char *s);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
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
