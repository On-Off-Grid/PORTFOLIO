/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:48:01 by souichou          #+#    #+#             */
/*   Updated: 2024/10/23 15:19:46 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *s)
{
	int	l;

	l = 0;
	while (*s)
	{
		l++;
		s++;
	}
	return (l);
}

/*#include <stdio.h>
int main()
{
	char *s = "the size is 14";

	printf("the length of s is: %d", ft_strlen(s));
}*/
