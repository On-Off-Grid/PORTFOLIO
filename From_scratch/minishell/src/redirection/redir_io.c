/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybareic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 04:38:46 by aybareic          #+#    #+#             */
/*   Updated: 2025/08/30 04:38:49 by aybareic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_regular_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_input_redir(t_redir *redir)
{
	if (redir->type == OP_IN)
		return (handle_regular_input(redir));
	else if (redir->type == OP_HEREDOC)
	{
		if (redir->heredoc_fd < 0)
		{
			ft_putstr_fd("minishell: heredoc not processed\n", STDERR_FILENO);
			return (1);
		}
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
		redir->heredoc_fd = -1;
		return (0);
	}
	return (0);
}

int	handle_output_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == OP_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == OP_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd < 0)
	{
		perror(redir->file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
