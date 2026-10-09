/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_file_ops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:37:55 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:37:56 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_temp_file(char *temp_file)
{
	int	fd;

	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror(temp_file);
		free(temp_file);
		return (-1);
	}
	return (fd);
}

int	finalize_heredoc_file(char *temp_file, int result)
{
	int	fd;

	if (result < 0 || g_signal == SIGINT)
	{
		unlink(temp_file);
		free(temp_file);
		return (-1);
	}
	fd = open(temp_file, O_RDONLY);
	free(temp_file);
	return (fd);
}
