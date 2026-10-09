/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:20:54 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:20:58 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(const char *cmd, const char *arg, const char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		if (arg)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(arg, 2);
		}
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	print_command_not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	print_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}

void	print_file_error(const char *filename, const char *error_type)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_type, 2);
}

void	print_permission_denied(const char *filename)
{
	print_file_error(filename, "Permission denied");
}
