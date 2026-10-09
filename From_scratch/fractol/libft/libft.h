/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <aybareic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:29:03 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:29:32 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*str_join_free(char *first, const char *second);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_echo(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*ft_itoa(int n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);

#endif
