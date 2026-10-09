/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:41 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:38:42 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_heredoc_file(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_RDONLY);
	if (fd < 0)
	{
		perror(tmp_file);
		unlink(tmp_file);
		free(tmp_file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(tmp_file);
	free(tmp_file);
	return (0);
}

int	handle_heredoc_signals(char *tmp_file, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(tmp_file);
		free(tmp_file);
		return (130);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(tmp_file);
		free(tmp_file);
		return (-1);
	}
	return (0);
}
