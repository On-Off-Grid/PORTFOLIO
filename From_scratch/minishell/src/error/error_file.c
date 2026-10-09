/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:19:54 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:20:07 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_no_such_file(const char *filename)
{
	print_file_error(filename, "No such file or directory");
}

void	print_is_directory(const char *filename)
{
	print_file_error(filename, "Is a directory");
}

int	validate_file_access(const char *filename, int mode)
{
	if (!filename)
		return (-1);
	if (access(filename, F_OK) != 0)
	{
		print_no_such_file(filename);
		return (-1);
	}
	if (access(filename, mode) != 0)
	{
		if (mode == R_OK)
			print_permission_denied(filename);
		else if (mode == W_OK)
			print_permission_denied(filename);
		else if (mode == X_OK)
			print_permission_denied(filename);
		return (-1);
	}
	return (0);
}

static int	check_output_directory(const char *filename)
{
	char	*dir;
	char	*last_slash;
	int		result;

	if (!filename)
		return (-1);
	last_slash = ft_strrchr(filename, '/');
	if (!last_slash)
		return (0);
	dir = ft_substr(filename, 0, last_slash - filename);
	if (!dir)
		return (-1);
	if (access(dir, F_OK) != 0)
	{
		print_no_such_file(dir);
		free(dir);
		return (-1);
	}
	result = validate_file_access(dir, W_OK | X_OK);
	free(dir);
	return (result);
}

int	check_output_file(const char *filename)
{
	if (check_output_directory(filename) != 0)
		return (-1);
	if (access(filename, F_OK) == 0)
	{
		if (validate_file_access(filename, W_OK) != 0)
			return (-1);
	}
	return (0);
}
