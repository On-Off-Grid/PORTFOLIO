/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:22:23 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:22:25 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

static int	check_min_args(const char *cmd, int argc, int min_args)
{
	if (argc < min_args)
	{
		print_error(cmd, NULL, "too few arguments");
		return (-1);
	}
	return (0);
}

static int	check_max_args(const char *cmd, int argc, int max_args)
{
	if (max_args > 0 && argc > max_args)
	{
		print_error(cmd, NULL, "too many arguments");
		return (-1);
	}
	return (0);
}

int	validate_builtin_args(const char *cmd, char **argv, int min_args,
	int max_args)
{
	int	argc;

	argc = count_args(argv);
	if (check_min_args(cmd, argc, min_args) != 0)
		return (-1);
	if (check_max_args(cmd, argc, max_args) != 0)
		return (-1);
	return (0);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
