/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:30:28 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:30 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv[1])
	{
		if (!is_valid_number(argv[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		if (argv[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		exit_code = ft_atoi(argv[1]);
	}
	exit(exit_code);
}
