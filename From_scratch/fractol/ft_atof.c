/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souichou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 09:05:44 by souichou          #+#    #+#             */
/*   Updated: 2025/03/22 09:08:07 by souichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_atof_decimal(const char *str, int *i)
{
	double	decimal;
	double	factor;

	decimal = 0.0;
	factor = 0.1;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			decimal += (str[*i] - '0') * factor;
			factor *= 0.1;
			(*i)++;
		}
	}
	return (decimal);
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	decimal = ft_atof_decimal(str, &i);
	return (sign * (result + decimal));
}

