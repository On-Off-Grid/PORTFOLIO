/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:19:48 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:19:50 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_fork_error(void)
{
	perror("fork");
	return (1);
}

int	handle_pipe_error(void)
{
	perror("pipe");
	return (1);
}

int	handle_execve_error(const char *cmd)
{
	print_command_not_found(cmd);
	return (127);
}

int	handle_redirection_error(const char *filename, int redir_type)
{
	if (redir_type == OP_IN || redir_type == OP_HEREDOC)
		return (validate_file_access(filename, R_OK));
	else
		return (check_output_file(filename));
}
